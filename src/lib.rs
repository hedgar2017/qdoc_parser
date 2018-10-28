mod error;
mod file;
pub mod entry;

extern crate pest;
#[macro_use]
extern crate pest_derive;
extern crate rayon;
#[macro_use]
extern crate failure;
extern crate percent_encoding;

use std::{collections::HashMap, fs};

use pest::{Parser, iterators::Pair};
use rayon::prelude::*;
use percent_encoding::{utf8_percent_encode, DEFAULT_ENCODE_SET};

use error::Error;
use entry::{QDocEntry, QDocItem, QDocEnum};
use file::QDocFile;

type QDocResult = Result<QDocFile, Error>;

pub enum QDocFilterable {
    Function,
    Overload,
    Parameter,
    LinkName,
    LinkUrl,
    LinkSeeAlso,
}

#[derive(Parser)]
#[grammar = "../peg/qdoc.peg"]
pub struct QDocParser<F>
    where
        F: Send + Sync + Fn(&str, QDocFilterable) -> String
{
    filter: F,
}

impl<F> QDocParser<F>
    where
        F: Send + Sync + Fn(&str, QDocFilterable) -> String
{
    pub fn new(filter: F) -> Self {
        Self {
            filter
        }
    }

    /// This is the main entry function that does all the work.
    /// paths = directory paths on the local harddrive for a directory of the Qt source code.
    ///        It's expected that all the files are parsed in parallel
    ///        (using rayon should make this easy)
    ///
    /// Filter should be called for each type/function entry. For example QMainWindow, aboutQt()
    /// and such text strings
    ///
    /// To allow the user to translate them if needed.
    /// If the user returns None the parser should output the data as is.
    ///
    pub fn parse_files(&self, paths: Vec<&str>) -> HashMap<String, QDocResult> {
        paths
            .par_iter()
            .map(|path| (path.to_string(), self.parse_file(path)))
            .collect::<HashMap<String, QDocResult>>()
    }

    fn parse_file(&self, path: &str) -> QDocResult {
        let data = fs::read_to_string(path)?;
        let data = match data.chars().last() {
            None => return Ok(QDocFile(Vec::new())),
            Some('\n') => data,
            Some(_) => data + "\n",
        }.replace("\r", "");        

        let file = Self::parse(Rule::doc_file, &data)
            .map_err(|error| Error::Parse(error.to_string()))?
            .next()
            .expect("file next() panic")
            .into_inner();
        let mut entries = Vec::with_capacity(64);

        'record: for record in file {
            match record.as_rule() {
                Rule::doc_entry => {
                    let mut entry = QDocEntry::default();
                    entry.qdoc_text = record.as_span().as_str().trim().to_owned();
                    for element in record.into_inner() {
                        match element.as_rule() {
                            Rule::doc_word => entry.rustdoc_elements.push(element.as_span().as_str().trim().to_owned()),
                            Rule::command => {
                                let command = element.into_inner().next().expect("command next() panic");
                                if let Rule::cmd_internal = command.as_rule() {
                                    continue 'record;
                                }
                                self.process_element(command, &mut entry);
                            }
                            Rule::newline => entry.rustdoc_elements.push("\n".to_string()),
                            Rule::function_line => {
                                if let QDocItem::Undefined = entry.data {
                                    entry.data = QDocItem::Function((self.filter)(element.as_span().as_str().trim(), QDocFilterable::Function));
                                }
                            }
                            _ => (),
                        }
                    }
                    entries.push(entry);
                }
                _ => (),
            };
        }
        Ok(QDocFile(entries))
    }

    fn process_element(&self, command: Pair<'_, Rule>, entry: &mut QDocEntry) {
        let command_text = command.as_span().as_str().trim();
        match command.as_rule() {
            Rule::cmd_a => {
                let word = command.into_inner().next().expect(&format!("\\a word next() panic: {}", command_text));
                match word.as_rule() {
                    Rule::doc_word | Rule::bracketed_doc_word => entry.rustdoc_elements.push(format!("*{}*", word.as_span().as_str().trim())),
                    _ => (),
                }
            },
            Rule::cmd_b | Rule::cmd_gui | Rule::cmd_underline => {
                let word = command.into_inner().next().expect(&format!("\\b word next() panic: {}", command_text));
                match word.as_rule() {
                    Rule::doc_word | Rule::bracketed_doc_word => entry.rustdoc_elements.push(format!("**{}**", word.as_span().as_str().trim())),
                    _ => (),
                }
            },
            Rule::cmd_brief => entry.brief = Some(command.as_span().as_str().trim().to_owned()),
            Rule::cmd_c => {
                let word = command.into_inner().next().expect(&format!("\\c word next() panic: {}", command_text));
                match word.as_rule() {
                    Rule::doc_word | Rule::bracketed_doc_word => entry.rustdoc_elements.push(format!("`{}`", word.as_span().as_str().trim())),
                    _ => (),
                }
            },
            Rule::cmd_code | Rule::cmd_legalese => entry.rustdoc_elements.push(format!("```\n    {} \n ```\n", command.as_span().as_str().trim())),
            Rule::cmd_class => entry.data = QDocItem::Class(command.as_span().as_str().trim().to_owned()),
            Rule::cmd_dots => entry.rustdoc_elements.push(format!("...")),
            Rule::cmd_e => {
                let word = command.into_inner().next().expect(&format!("\\e word next() panic: {}", command_text));
                match word.as_rule() {
                    Rule::doc_word | Rule::bracketed_doc_word => entry.rustdoc_elements.push(format!("*{}*", word.as_span().as_str().trim())),
                    _ => (),
                }
            },
            Rule::cmd_enum => entry.data = QDocItem::Enum(QDocEnum{name: command.as_span().as_str().trim().to_owned(), data: HashMap::new()}),
            Rule::cmd_fn => entry.data = QDocItem::Function((self.filter)(command.as_span().as_str().trim(), QDocFilterable::Function)),
            Rule::cmd_image | Rule::cmd_inlineimage => {
                let mut name = "";
                let mut desc = "";
                for part in command.into_inner() {
                    match part.as_rule() {
                        Rule::image_name => name = part.as_span().as_str().trim(),
                        Rule::image_description => desc = part.as_span().as_str().trim(),
                        _ => (),
                    }
                }
                if desc == "" {
                    desc = name;
                }
                entry.rustdoc_elements.push(format!("![{}]({})\n\n", desc, name));
            },
            Rule::cmd_inmodule => entry.module = Some(command.as_span().as_str().trim().to_owned()),
            Rule::cmd_keyword => entry.rustdoc_elements.push(format!("**Keyword**:")),
            Rule::cmd_l => {
                let mut _page = "";
                let mut target = "";
                let mut text = "";
                for part in command.into_inner() {
                    match part.as_rule() {
                        Rule::link_page => _page = part.as_span().as_str().trim(),
                        Rule::link_target_single | Rule::link_target_multi => target = part.as_span().as_str().trim(),
                        Rule::link_name_multi => text = part.as_span().as_str().trim(),
                        _ => (),
                    }
                }
                if text == "" {
                    text = target;
                }
                let text = (self.filter)(text, QDocFilterable::LinkName);
                let target = (self.filter)(target, QDocFilterable::LinkUrl);
                entry.rustdoc_elements.push(format!("[{}]({})\n", text, utf8_percent_encode(&target, DEFAULT_ENCODE_SET)));
            },
            Rule::cmd_li | Rule::cmd_o => {                
                entry.rustdoc_elements.push(format!("*"));
                for element in command.into_inner() {
                    match element.as_rule() {
                        Rule::doc_word => entry.rustdoc_elements.push(element.as_span().as_str().trim().to_owned()),
                        Rule::command => {
                            let command = element.into_inner().next().expect("command next() panic");
                            self.process_element(command, entry);
                        }
                        _ => (),
                    }
                }
                entry.rustdoc_elements.push(format!("\n"));
            }
            Rule::cmd_macos => entry.rustdoc_elements.push(format!("MacOS")),
            Rule::cmd_macro => entry.data = QDocItem::Macro(command.as_span().as_str().trim().to_owned()),
            Rule::cmd_namespace => entry.namespace = Some(command.as_span().as_str().trim().to_owned()),
            Rule::cmd_note => entry.rustdoc_elements.push(format!("**Note**:")),
            Rule::cmd_overload => entry.rustdoc_elements.push(format!("**Overloads** {}", (self.filter)(command.as_span().as_str().trim(), QDocFilterable::Overload))),
            Rule::cmd_param => entry.rustdoc_elements.push(format!("**Parameter** {}", (self.filter)(command.as_span().as_str().trim(), QDocFilterable::Parameter))),
            Rule::cmd_property => entry.data = QDocItem::Property(command.as_span().as_str().trim().to_owned()),
            Rule::cmd_return => entry.rustdoc_elements.push(format!("**Returns**")),
            Rule::cmd_sa => {
                entry.rustdoc_elements.push(format!("**See also:**"));
                for part in command.into_inner() {
                    if let Rule::sa_link = part.as_rule() {
                        entry.rustdoc_elements.push(format!("{}\n", (self.filter)(part.as_span().as_str().trim(), QDocFilterable::LinkSeeAlso)));
                    }
                }
            },
            Rule::cmd_section1 => entry.rustdoc_elements.push(format!("# {}\n", command.as_span().as_str().trim())),
            Rule::cmd_section2 => entry.rustdoc_elements.push(format!("## {}\n", command.as_span().as_str().trim())),
            Rule::cmd_section3 => entry.rustdoc_elements.push(format!("### {}\n", command.as_span().as_str().trim())),
            Rule::cmd_section4 => entry.rustdoc_elements.push(format!("#### {}\n", command.as_span().as_str().trim())),
            Rule::cmd_struct => entry.data = QDocItem::Struct(command.as_span().as_str().trim().to_owned()),
            Rule::cmd_sup => entry.rustdoc_elements.push(format!("^{}", command.as_span().as_str().trim())),
            Rule::cmd_title => entry.title = Some(command.as_span().as_str().trim().to_owned()),
            Rule::cmd_tt => {
                let word = command.into_inner().next().expect(&format!("\\tt word next() panic: {}", command_text));
                match word.as_rule() {
                    Rule::doc_word | Rule::bracketed_doc_word => entry.rustdoc_elements.push(format!("`{}`", word.as_span().as_str().trim())),
                    _ => (),
                }
            },
            Rule::cmd_unicode => {
                let word = command.into_inner().next().expect(&format!("\\unicode word next() panic: {}", command_text));
                match word.as_rule() {
                    Rule::doc_word | Rule::bracketed_doc_word => entry.rustdoc_elements.push(format!("&#x{};", word.as_span().as_str().trim())),
                    _ => (),
                }
            },
            Rule::cmd_uicontrol => entry.rustdoc_elements.push(format!("**{}**", command.as_span().as_str().trim())),
            Rule::cmd_value => {
                let mut key = "";
                let mut description = "";
                for part in command.into_inner() {
                    match part.as_rule() {
                        Rule::enum_value_key => key = part.as_span().as_str().trim(),
                        Rule::enum_value_description => description = part.as_span().as_str().trim(),
                        _ => (),
                    }
                }
                if let QDocItem::Enum(ref mut value) = entry.data {
                    value.data.insert(key.to_owned(), description.to_owned());
                }
            },
            Rule::cmd_variable => entry.data = QDocItem::Variable(command.as_span().as_str().trim().to_owned()),
            Rule::cmd_warning => entry.rustdoc_elements.push(format!("**Warning**:")),
            _ => (),
        }
    }
}
