pub mod entry;
mod error;
mod file;

extern crate pest;
#[macro_use]
extern crate pest_derive;
extern crate rayon;
#[macro_use]
extern crate failure;
extern crate percent_encoding;
extern crate walkdir;

use std::path::PathBuf;
use walkdir::{DirEntry, WalkDir};

use std::{collections::HashMap, fs};

use percent_encoding::{utf8_percent_encode, DEFAULT_ENCODE_SET};
use pest::{iterators::Pair, Parser};
use rayon::prelude::*;

pub use entry::{QDocEntry, QDocEnum, QDocItem};
pub use file::QDocFile;

use error::Error;

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
    F: Send + Sync + Fn(&str, QDocFilterable) -> String,
{
    filter: F,
}

fn is_private_file(entry: &walkdir::DirEntry) -> bool {
    entry.path().to_str().unwrap().contains("private")
}

fn is_cpp(entry: &DirEntry) -> bool {
    entry
        .file_name()
        .to_str()
        .map(|s| s.ends_with(".cpp") || s.ends_with("qnamespace.qdoc"))
        .unwrap_or(false)
}
///
/// Function for adding files/paths to process
///
fn add_process_path(dest: &mut Vec<PathBuf>, path: &str) {
    for entry in WalkDir::new(path) {
        let entry = entry.unwrap();

        if is_private_file(&entry) {
            continue;
        }

        if !is_cpp(&entry) {
            continue;
        }

        dest.push(entry.path().to_owned());
    }
}

impl<F> QDocParser<F>
where
    F: Send + Sync + Fn(&str, QDocFilterable) -> String,
{
    pub fn new(filter: F) -> Self {
        Self { filter }
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
    pub fn parse_files(&self, paths: &[String]) -> HashMap<String, QDocFile> {
        let mut files: Vec<PathBuf> = Vec::new();

        for p in paths {
            add_process_path(&mut files, p);
        }

        files
            .par_iter()
            .map(|path| {
                let p = path.to_owned().into_os_string().into_string().unwrap();
                (p.to_owned(), self.parse_file(&p).unwrap())
            }).collect::<HashMap<String, QDocFile>>()
    }

    fn parse_file(&self, path: &str) -> QDocResult {
        println!("Doc parsing {}", path);
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
                            Rule::doc_word => entry
                                .rustdoc_elements
                                .push(element.as_span().as_str().trim().to_owned()),
                            Rule::command => {
                                let command =
                                    element.into_inner().next().expect("command next() panic");
                                if let Rule::cmd_internal = command.as_rule() {
                                    continue 'record;
                                }
                                if let Some(data) = self.process_element(command, &mut entry) {
                                    entry.rustdoc_elements.push(data.to_owned());
                                }
                            }
                            Rule::newline => entry.rustdoc_elements.push("\n".to_string()),
                            Rule::function_line => {
                                if let QDocItem::Undefined = entry.data {
                                    entry.data = QDocItem::Function((self.filter)(
                                        element.as_span().as_str().trim(),
                                        QDocFilterable::Function,
                                    ));
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

    fn process_element(&self, command: Pair<'_, Rule>, entry: &mut QDocEntry) -> Option<String> {
        let command_text = command.as_span().as_str().trim();
        match command.as_rule() {
            Rule::cmd_a => {
                let word = command
                    .into_inner()
                    .next()
                    .expect(&format!("\\a word next() panic: {}", command_text));
                let data = format!("*{}*", word.as_span().as_str().trim());
                return Some(data);
            }
            Rule::cmd_b | Rule::cmd_gui | Rule::cmd_underline => {
                let word = command
                    .into_inner()
                    .next()
                    .expect(&format!("\\b word next() panic: {}", command_text));
                let data = format!("**{}**", word.as_span().as_str().trim());
                return Some(data);
            }
            Rule::cmd_brief => entry.brief = Some(command.as_span().as_str().trim().to_owned()),
            Rule::cmd_c => {
                let word = command
                    .into_inner()
                    .next()
                    .expect(&format!("\\c word next() panic: {}", command_text));
                let data = format!("`{}`", word.as_span().as_str().trim());
                return Some(data);
            }
            Rule::cmd_code | Rule::cmd_legalese => {
                let data = format!(
                    "```\n    {} \n ```\n",
                    command.as_span().as_str().trim()
                );
                return Some(data);
            },
            Rule::cmd_class => {
                entry.data = QDocItem::Class(command.as_span().as_str().trim().to_owned())
            }
            Rule::cmd_dots => return Some(format!("...")),
            Rule::cmd_e => {
                let word = command
                    .into_inner()
                    .next()
                    .expect(&format!("\\e word next() panic: {}", command_text));
                let data = format!("*{}*", word.as_span().as_str().trim());
                return Some(data);
            }
            Rule::cmd_enum => {
                let mut name = "";
                let mut description = Vec::new();
                for part in command.into_inner() {
                    match part.as_rule() {
                        Rule::enum_name => name = part.as_span().as_str().trim(),
                        Rule::enum_description => {
                            for element in part.into_inner() {
                                match element.as_rule() {
                                    Rule::doc_word => description.push(element.as_span().as_str().trim().to_owned()),
                                    Rule::command => {
                                        let command =
                                            element.into_inner().next().expect("command next() panic");
                                        if let Some(text) = self.process_element(command, entry) {
                                            description.push(text);
                                        }
                                    }
                                    _ => (),
                                }
                            }
                        },
                        _ => (),
                    }
                }
                entry.data = QDocItem::Enum(QDocEnum {
                    name: name.to_owned(),
                    description: description.join(" "),
                    data: HashMap::new(),
                })
            }
            Rule::cmd_fn => {
                entry.data = QDocItem::Function((self.filter)(
                    command.as_span().as_str().trim(),
                    QDocFilterable::Function,
                ))
            }
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
                return Some(format!("![{}]({})\n\n", desc, name));
            }
            Rule::cmd_inmodule => entry.module = Some(command.as_span().as_str().trim().to_owned()),
            Rule::cmd_keyword => return Some(format!("**Keyword**:")),
            Rule::cmd_l => {
                let mut _page = "";
                let mut target = "";
                let mut text = "";
                for part in command.into_inner() {
                    match part.as_rule() {
                        Rule::link_page => _page = part.as_span().as_str().trim(),
                        Rule::link_target_single | Rule::link_target_multi => {
                            target = part.as_span().as_str().trim()
                        }
                        Rule::link_name_multi => text = part.as_span().as_str().trim(),
                        _ => (),
                    }
                }
                if text == "" {
                    text = target;
                }
                let text = (self.filter)(text, QDocFilterable::LinkName);
                let target = (self.filter)(target, QDocFilterable::LinkUrl);
                let data = format!(
                    "[{}]({})\n",
                    text,
                    utf8_percent_encode(&target, DEFAULT_ENCODE_SET)
                );
                return Some(data);
            }
            Rule::cmd_li | Rule::cmd_o => {
                let mut data = Vec::new();
                data.push(format!("*"));
                for element in command.into_inner() {
                    match element.as_rule() {
                        Rule::doc_word => data.push(element.as_span().as_str().trim().to_owned()),
                        Rule::command => {
                            let command =
                                element.into_inner().next().expect("command next() panic");
                            if let Some(text) = self.process_element(command, entry) {
                                data.push(text);
                            }
                        }
                        _ => (),
                    }
                }
                data.push(format!("\n"));
                return Some(data.join(" "));
            }
            Rule::cmd_macos => {
                return Some("MacOS".to_string());
            },
            Rule::cmd_macro => {
                entry.data = QDocItem::Macro(command.as_span().as_str().trim().to_owned())
            }
            Rule::cmd_namespace => {
                entry.namespace = Some(command.as_span().as_str().trim().to_owned())
            }
            Rule::cmd_note => return Some(format!("**Note**:")),
            Rule::cmd_overload => return Some(format!(
                "**Overloads** {}",
                (self.filter)(command.as_span().as_str().trim(), QDocFilterable::Overload)
            )),
            Rule::cmd_param => return Some(format!(
                "**Parameter** {}",
                (self.filter)(command.as_span().as_str().trim(), QDocFilterable::Parameter)
            )),
            Rule::cmd_property => {
                entry.data = QDocItem::Property(command.as_span().as_str().trim().to_owned())
            }
            Rule::cmd_return => return Some(format!("**Returns**")),
            Rule::cmd_sa => {
                let mut data = Vec::new();
                data.push(format!("**See also:**"));
                for part in command.into_inner() {
                    if let Rule::sa_link = part.as_rule() {
                        data.push(format!(
                            "{}\n",
                            (self.filter)(
                                part.as_span().as_str().trim(),
                                QDocFilterable::LinkSeeAlso
                            )
                        ));
                    }
                }
                return Some(data.join(" "));
            }
            Rule::cmd_section1 => return Some(format!("# {}\n", command.as_span().as_str().trim())),
            Rule::cmd_section2 => return Some(format!("## {}\n", command.as_span().as_str().trim())),
            Rule::cmd_section3 => return Some(format!("### {}\n", command.as_span().as_str().trim())),
            Rule::cmd_section4 => return Some(format!("#### {}\n", command.as_span().as_str().trim())),
            Rule::cmd_struct => {
                entry.data = QDocItem::Struct(command.as_span().as_str().trim().to_owned())
            }
            Rule::cmd_sup => return Some(format!("^{}", command.as_span().as_str().trim())),
            Rule::cmd_title => entry.title = Some(command.as_span().as_str().trim().to_owned()),
            Rule::cmd_tt => {
                let word = command
                    .into_inner()
                    .next()
                    .expect(&format!("\\tt word next() panic: {}", command_text));
                return Some(format!("`{}`", word.as_span().as_str().trim().to_owned()));
            }
            Rule::cmd_unicode => {
                let word = command
                    .into_inner()
                    .next()
                    .expect(&format!("\\unicode word next() panic: {}", command_text));
                let data = format!("&#x{};", word.as_span().as_str().trim());
                return Some(data);
            }
            Rule::cmd_uicontrol => return Some(format!("**{}**", command.as_span().as_str().trim())),
            Rule::cmd_value => {
                let mut key = "";
                let mut description = Vec::new();
                for part in command.into_inner() {
                    match part.as_rule() {
                        Rule::enum_value_key => key = part.as_span().as_str().trim(),
                        Rule::enum_value_description => {
                            for element in part.into_inner() {
                                match element.as_rule() {
                                    Rule::doc_word => description.push(element.as_span().as_str().trim().to_owned()),
                                    Rule::command => {
                                        let command =
                                            element.into_inner().next().expect("command next() panic");
                                        if let Some(text) = self.process_element(command, entry) {
                                            description.push(text);
                                        }
                                    }
                                    _ => (),
                                }
                            }
                        }
                        _ => (),
                    }
                }
                if let QDocItem::Enum(ref mut value) = entry.data {
                    value.data.insert(key.to_owned(), description.join(" "));
                }
            }
            Rule::cmd_variable => {
                entry.data = QDocItem::Variable(command.as_span().as_str().trim().to_owned())
            }
            Rule::cmd_warning => return Some(format!("**Warning**:")),
            _ => (),
        };
        None
    }
}
