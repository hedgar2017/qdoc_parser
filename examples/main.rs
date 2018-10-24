extern crate qdoc_parser;

use qdoc_parser::QDocParser;

fn main() {
    let info = QDocParser::parse_files(vec![
        "examples/example1.cpp",
        // "examples/example1.cpp",
        // "examples/example1.cpp",
    ]);
    for (file, result) in info {
        match result {
            Ok(entries) => for (index, entry) in entries.iter().enumerate() {
                println!("Entry {}\n{}", index, entry);
            },
            Err(error) => eprintln!("Error with file {}: {}", file, error.to_string()),
        }
    }
}
