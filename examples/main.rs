//!
//! This example can be used for testing with entire Qt sources.
//! Just git clone [Qt source code](https://github.com/qt/qtbase) and run with some script:
//! for file in .../qtbase/**/*.cpp; do .../main "${file}" 2>&1 1>/dev/null | tee -a test.log
//!

extern crate qdoc_parser;

use std::env;

use qdoc_parser::{QDocFilterable, QDocParser};

fn main() {
    let filter = |value_data: &str, value_type: QDocFilterable| {
        use QDocFilterable::*;

        match value_type {
            Function => format!("FilteredFunction{}", value_data),
            Overload => format!("FilteredOverload{}", value_data),
            Parameter => format!("FilteredParameter{}", value_data),
            LinkName => format!("FilteredLinkName{}", value_data),
            LinkUrl => format!("FilteredLinkUrl{}", value_data),
            LinkSeeAlso => format!("FilteredLinkSeeAlso{}", value_data),
        }
    };

    let files = if let Some(file_arg) = env::args().collect::<Vec<String>>().get(1) {
        vec![file_arg.to_owned()]
    } else {
        vec!["cpp/example.cpp".to_owned()]
    };

    let info = QDocParser::new(filter).parse_files(&files);

    for (path, file_data) in info {
        eprintln!("{}", path);
        println!("{}", file_data);
    }
}
