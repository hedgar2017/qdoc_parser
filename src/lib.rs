extern crate pest;
#[macro_use]
extern crate pest_derive;

use std::fs;

use pest::Parser;

#[derive(Parser)]
#[grammar = "grammar.peg"]
pub struct DocParser;

impl DocParser {
    /// This is the main entry function that does all the work.
    /// paths = directory paths on the local harddrive for a directory of the Qt source code.
    ///        It's expected that all the files are paresed in parallel
    ///        (using rayon should make this easy)
    ///
    /// Filter should be called for each type/function entry. For example QMainWindow, aboutQt()
    /// and such text strings
    ///
    /// To allow the user to translate them if needed.
    /// If the user returns None the parser should output the data as is.
    ///
    pub fn parse_files(paths: &[&str]) -> Vec<DocInfo> {
        paths.iter().map(|path| Self::parse_file(path)).collect::<Vec<DocInfo>>()        
    }

    fn parse_file(path: &str) -> DocInfo {
        let data = fs::read_to_string(path).expect("cannot read file");
        let file = Self::parse(Rule::doc_file, &data).expect("cannot parse file").next().unwrap().into_inner();
        let mut entries = Vec::with_capacity(64);
        for record in file {
            match record.as_rule() {
                Rule::comment_singleline => entries.push(DocEntry {
                    target_cpp_function: None,
                    qdoc_text: record.as_span().as_str().to_owned(),
                    rustdoc_text: String::new(),
                }),
                Rule::comment_multiline => entries.push(DocEntry {
                    target_cpp_function: None,
                    qdoc_text: record.as_span().as_str().to_owned(),
                    rustdoc_text: String::new(),
                }),
                _ => (),
            };
        }
        DocInfo {
            entries,
            path: path.to_owned(),
        }
    }
}

#[derive(Debug)]
pub struct DocInfo {
    /// List of all the parsed entries
    pub entries: Vec<DocEntry>,
    /// Filename where all the docs where parsed
    pub path: String,
}

///
/// This is a doc entry that represent one section of the Qt
/// mark up (whatever comes between /*! ... */)"
///
#[derive(Debug)]
pub struct DocEntry {
    /// If this is set it means that the doc entry is atteached to a cpp function
    pub target_cpp_function: Option<String>,
    /// This has the original QDoc text in it
    pub qdoc_text: String,
    /// This has the RustDoc translated/converted text in it
    pub rustdoc_text: String,
}
