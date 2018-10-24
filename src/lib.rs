mod file;
mod entry;

extern crate pest;
#[macro_use]
extern crate pest_derive;
extern crate rayon;
#[macro_use]
extern crate failure;

use std::{collections::HashMap, fs, io};

use pest::Parser;
use rayon::prelude::*;

use file::QDocFile;
use entry::QDocEntry;

#[derive(Parser)]
#[grammar = "grammar.peg"]
pub struct QDocParser;

#[derive(Debug, Fail)]
pub enum Error {
    #[fail(display = "File reading error: {}", _0)]
    Read(io::Error),
    #[fail(display = "File is empty")]
    Empty,
    #[fail(display = "File parsing error:\n{}", _0)]
    Parse(String),
}

impl From<io::Error> for Error {
    fn from(error: io::Error) -> Self {
        Error::Read(error)
    }
}

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
            None => return Err(Error::Empty),
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
                Rule::comment_singleline => (),
                Rule::comment_multiline => {
                    let qdoc_text = record.as_span().as_str().trim().to_owned();

                    let mut rustdoc_lines = Vec::with_capacity(64);
                    for line in record.into_inner() {
                        match line.as_rule() {
                            Rule::comment_line => {
                                rustdoc_lines.push(format!("/// {}", line.as_span().as_str().trim()));
                            }
                            _ => (),
                        }
                    }
                    let rustdoc_text = rustdoc_lines.join("\n").trim().to_owned();

                    entries.push(QDocEntry {
                        target_cpp_function: None,
                        qdoc_text,
                        rustdoc_text,
                    });
                }
                _ => (),
            };
        }
        Ok(QDocFile(entries))
    }
}
