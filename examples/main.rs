extern crate qdoc_parser;

use qdoc_parser::QDocParser;

fn main() {
    let info = QDocParser::parse_files(vec![
        "examples/example1.cpp",
        "examples/example1.cpp",
        "examples/example1.cpp",
        "examples/example1.cpp",
        "examples/example1.cpp",
        "examples/example1.cpp",
        "examples/example1.cpp",
        "examples/example1.cpp",
    ]);
    for (path, result) in info {
        match result {
            Ok(file) => println!("{}", file),
            Err(error) => eprintln!("Error with file {}: {}", path, error.to_string()),
        }
    }
}
