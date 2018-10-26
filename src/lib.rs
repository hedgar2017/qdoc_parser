mod entry;
mod error;
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

use entry::QDocEntry;
use error::Error;
use file::QDocFile;

#[derive(Parser)]
#[grammar = "../peg/qdoc.peg"]
pub struct QDocParser;

type QDocResult = Result<QDocFile, Error>;

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
                Rule::doc_singleline | Rule::doc_multiline => {
                    let mut class_name = None;
                    let mut target_cpp_function = None;
                    let mut qdoc_lines = Vec::with_capacity(64);
                    let mut rustdoc_lines = Vec::with_capacity(64);

                    for line in record.into_inner() {
                        match line.as_rule() {
                            Rule::doc_line => {
                                let line_text = line.as_span().as_str().trim();
                                qdoc_lines.push(line_text);

                                let words = line
                                    .into_inner()
                                    .map(|pair| pair.as_span().as_str().trim())
                                    .collect::<Vec<&str>>();
                                class_name = class_name.or(Self::check_for_class(&words));
                                rustdoc_lines.push(line_text);
                            }
                            Rule::function_line => {
                                if class_name.is_none() {
                                    target_cpp_function =
                                        Some(line.as_span().as_str().trim().to_owned());
                                }
                            }
                            _ => (),
                        }
                    }

                    entries.push(QDocEntry {
                        class_name,
                        target_cpp_function,
                        qdoc_text: qdoc_lines.join("\n").trim().to_owned(),
                        rustdoc_text: rustdoc_lines.join("\n").trim().to_owned(),
                    });
                }
                _ => (),
            };
        }
        Ok(QDocFile(entries))
    }

    fn check_for_class(words: &[&str]) -> Option<String> {
        if words.len() < 2 {
            return None;
        }
        if words[0] == "\\class" {
            return Some(words[1..].join(" "));
        }
        None
    }
}
