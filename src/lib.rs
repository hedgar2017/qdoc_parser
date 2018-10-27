mod error;
mod file;
pub mod entry;

extern crate pest;
#[macro_use]
extern crate pest_derive;
extern crate rayon;
#[macro_use]
extern crate failure;

use std::{collections::HashMap, fs};

use pest::Parser;
use rayon::prelude::*;

use error::Error;
use entry::{QDocEntry, QDocItem, QDocEnum};
use file::QDocFile;

type QDocResult = Result<QDocFile, Error>;

#[derive(Parser)]
#[grammar = "../peg/qdoc.peg"]
pub struct QDocParser;

impl QDocParser {
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
    pub fn parse_files(paths: Vec<&str>) -> HashMap<String, QDocResult> {
        paths
            .par_iter()
            .map(|path| (path.to_string(), Self::parse_file(path)))
            .collect::<HashMap<String, QDocResult>>()
    }

    fn parse_file(path: &str) -> QDocResult {
        let data = fs::read_to_string(path)?;
        let data = match data.chars().last() {
            None => return Ok(QDocFile(Vec::new())),
            Some('\n') => data.replace("\r\n", "\n"),
            Some(_) => data.replace("\r\n", "\n") + "\n",
        };

        let file = Self::parse(Rule::doc_file, &data)
            .map_err(|error| Error::Parse(error.to_string()))?
            .next()
            .unwrap()
            .into_inner();
        let mut entries = Vec::with_capacity(64);

        'record: for record in file {
            match record.as_rule() {
                Rule::doc_entry => {
                    let mut entry = QDocEntry::default();
                    entry.qdoc_text = record.as_span().as_str().to_owned();

                    let mut rustdoc_lines = Vec::with_capacity(64);
                    for element in record.into_inner() {
                        match element.as_rule() {
                            Rule::doc_word => rustdoc_lines.push(element.as_span().as_str().to_owned()),
                            Rule::command => {
                                let command = element.into_inner().next().unwrap();
                                match command.as_rule() {
                                    Rule::cmd_a => {
                                        let word = command.into_inner().next().unwrap();
                                        match word.as_rule() {
                                            Rule::doc_word | Rule::bracketed_doc_word => rustdoc_lines.push(format!("*{}*", word.as_span().as_str().trim())),
                                            _ => (),
                                        }
                                    },
                                    Rule::cmd_b | Rule::cmd_gui | Rule::cmd_underline => {
                                        let word = command.into_inner().next().unwrap();
                                        match word.as_rule() {
                                            Rule::doc_word | Rule::bracketed_doc_word => rustdoc_lines.push(format!("**{}**", word.as_span().as_str().trim())),
                                            _ => (),
                                        }
                                    },
                                    Rule::cmd_brief => entry.brief = Some(command.as_span().as_str().trim().to_owned()),
                                    Rule::cmd_c | Rule::cmd_codeline => {
                                        let word = command.into_inner().next().unwrap();
                                        match word.as_rule() {
                                            Rule::doc_word | Rule::bracketed_doc_word => rustdoc_lines.push(format!("`{}`", word.as_span().as_str().trim())),
                                            _ => (),
                                        }
                                    },                                    
                                    Rule::cmd_code | Rule::cmd_legalese => rustdoc_lines.push(format!("```\n    {} \n ```\n", command.as_span().as_str().trim())),
                                    Rule::cmd_class => entry.data = QDocItem::Class(command.as_span().as_str().trim().to_owned()),
                                    Rule::cmd_dots => rustdoc_lines.push(format!("...")),
                                    Rule::cmd_e => {
                                        let word = command.into_inner().next().unwrap();
                                        match word.as_rule() {
                                            Rule::doc_word | Rule::bracketed_doc_word => rustdoc_lines.push(format!("*{}*", word.as_span().as_str().trim())),
                                            _ => (),
                                        }
                                    },
                                    Rule::cmd_enum => entry.data = QDocItem::Enum(QDocEnum{name: command.as_span().as_str().trim().to_owned(), data: HashMap::new()}),
                                    Rule::cmd_fn => entry.data = QDocItem::Function(command.as_span().as_str().trim().to_owned()),
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
                                        rustdoc_lines.push(format!("![{}]({})\n\n", desc, name));
                                    },
                                    Rule::cmd_inmodule => entry.module = Some(command.as_span().as_str().trim().to_owned()),
                                    Rule::cmd_internal => continue 'record,
                                    Rule::cmd_l => {
                                        let mut _page = "";
                                        let mut target = "";
                                        let mut text = "";
                                        for part in command.into_inner() {
                                            match part.as_rule() {
                                                Rule::link_page => _page = part.as_span().as_str().trim(),
                                                Rule::link_target_single | Rule::link_target_multi => target = part.as_span().as_str().trim(),
                                                Rule::link_name_single | Rule::link_name_multi => text = part.as_span().as_str().trim(),
                                                _ => (),
                                            }
                                        }
                                        if text == "" {
                                            text = target;
                                        }
                                        rustdoc_lines.push(format!("[{}]({})\n", text, target));
                                    },
                                    Rule::cmd_li => rustdoc_lines.push(format!("*")),
                                    Rule::cmd_macos => rustdoc_lines.push(format!("MacOS")),
                                    Rule::cmd_macro => entry.data = QDocItem::Macro(command.as_span().as_str().trim().to_owned()),
                                    Rule::cmd_note => rustdoc_lines.push(format!("**Note**: {}\n", command.as_span().as_str().trim().replace("\n", " "))),
                                    Rule::cmd_overload => (),
                                    Rule::cmd_property => entry.data = QDocItem::Property(command.as_span().as_str().trim().to_owned()),
                                    Rule::cmd_sa => {
                                        for part in command.into_inner() {
                                            match part.as_rule() {
                                                Rule::sa_link => rustdoc_lines.push(format!("{}\n", part.as_span().as_str())),
                                                _ => (),
                                            }
                                        }
                                    },
                                    Rule::cmd_section1 => rustdoc_lines.push(format!("# {}\n", command.as_span().as_str().trim())),
                                    Rule::cmd_section2 => rustdoc_lines.push(format!("## {}\n", command.as_span().as_str().trim())),
                                    Rule::cmd_section3 => rustdoc_lines.push(format!("### {}\n", command.as_span().as_str().trim())),
                                    Rule::cmd_section4 => rustdoc_lines.push(format!("#### {}\n", command.as_span().as_str().trim())),
                                    Rule::cmd_uicontrol => rustdoc_lines.push(format!("**{}**", command.as_span().as_str().trim())),
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
                                    Rule::cmd_warning => rustdoc_lines.push(format!("**Warning**: {}\n", command.as_span().as_str().trim())),
                                    _ => (),
                                }
                            }
                            Rule::newline => rustdoc_lines.push("\n".to_string()),
                            Rule::function_line => {
                                if let QDocItem::Undefined = entry.data {
                                    entry.data = QDocItem::Function(element.as_span().as_str().trim().to_owned());
                                }
                            }
                            _ => (),
                        }
                    }

                    entry.rustdoc_text = rustdoc_lines.join(" ").to_owned();
                    entries.push(entry);
                }
                _ => (),
            };
        }
        Ok(QDocFile(entries))
    }
}
