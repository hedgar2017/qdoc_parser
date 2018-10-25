//!
//! This example can be used for testing with entire Qt sources.
//! Just git clone [Qt source code](https://github.com/qt/qtbase) and run with some script:
//! for file in .../qtbase/**/*.cpp; do .../main "${file}" 2>&1 1>/dev/null | tee -a test.log
//! 

extern crate qdoc_parser;

use std::env;

use qdoc_parser::QDocParser;

fn main() {
    let info = QDocParser::parse_files(vec![
        env::args()
            .collect::<Vec<String>>()
            .get(1)
            .unwrap_or(&"cpp/example.cpp".to_owned()),
    ]);
    for (path, result) in info {
        match result {
            Ok(file) => {
                eprintln!("Ok with file {}", path);
                println!("{}", file);
            },
            Err(error) => eprintln!("Error with file {}: {}", path, error.to_string()),
        }
    }
}
