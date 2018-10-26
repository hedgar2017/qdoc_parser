mod error;
mod entry;
mod file;

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
use entry::QDocEntry;
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
            Some('\n') => data,
            Some(_) => data + "\n",
        };

        let file = Self::parse(Rule::doc_file, &data)
            .map_err(|error| Error::Parse(error.to_string()))?
            .next()
            .unwrap()
            .into_inner();
        let mut entries = Vec::with_capacity(64);

        for record in file {
            match record.as_rule() {
                Rule::doc_entry => {
                    let mut class = None;
                    let mut brief = None;
                    let mut function = None;

                    let qdoc_text = record.as_span().as_str().to_owned();
                    let mut rustdoc_lines = Vec::with_capacity(64);

                    for element in record.into_inner() {
                        match element.as_rule() {
                            Rule::doc_word => {
                                let text = element.as_span().as_str();
                                rustdoc_lines.push(format!("{} ", text));
                            }
                            Rule::command => {
                                let command = element.into_inner().next().unwrap();
                                println!("Command: {}", command.as_span().as_str());
                                match command.as_rule() {
                                    Rule::cmd_a => {
                                        let text = command.as_span().as_str().trim();
                                        rustdoc_lines.push(format!("*{}*", text));
                                    },
                                    Rule::cmd_b | Rule::cmd_gui => {
                                        let text = command.as_span().as_str().trim();
                                        rustdoc_lines.push(format!("**{}**", text));
                                    },
                                    Rule::cmd_brief => {
                                        brief = Some(command.as_span().as_str().trim().to_owned());
                                    },
                                    Rule::cmd_c | Rule::cmd_code | Rule::cmd_codeline => {
                                        let text = command.as_span().as_str().trim();
                                        rustdoc_lines.push(format!("`{}`", text));
                                    },
                                    Rule::cmd_class => {
                                        class = Some(command.as_span().as_str().trim().to_owned());
                                    },
                                    Rule::cmd_dots => {
                                        rustdoc_lines.push(format!("..."));
                                    },
                                    Rule::cmd_e => {
                                        let text = command.as_span().as_str().trim();
                                        rustdoc_lines.push(format!("*{}*", text));
                                    },
                                    Rule::cmd_fn => {
                                        function = Some(command.as_span().as_str().trim().to_owned());
                                    },
                                    _ => (),
                                }
                            }
                            Rule::newline => rustdoc_lines.push("\n".to_string()),
                            Rule::function_line => {
                                if class.is_none() && function.is_none() {
                                    function =
                                        Some(element.as_span().as_str().trim().to_owned());
                                }
                            }
                            _ => (),
                        }
                    }

                    for (i, v) in rustdoc_lines.iter().enumerate() {
                        println!("{}: {}", i, v);
                    }

                    entries.push(QDocEntry {
                        class,
                        brief,
                        function,
                        qdoc_text,
                        rustdoc_text: rustdoc_lines.join("").to_owned(),
                    });
                }
                _ => (),
            };
        }
        Ok(QDocFile(entries))
    }
}
