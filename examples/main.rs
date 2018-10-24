extern crate qdoc_parser;

use qdoc_parser::DocParser;

fn main() {
    let info = DocParser::parse_files(&["examples/example.cpp"]);
    for file in info {
        for entry in file.entries {
            println!("{:?}", entry.qdoc_text.split("\r\n").collect::<Vec<&str>>());
        }
    }
}
