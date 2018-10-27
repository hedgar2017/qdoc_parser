extern crate qdoc_parser;

use std::env;
use std::fs::File;
use std::io::BufWriter;
use std::io::Write;

use qdoc_parser::entry::QDocItem;
use qdoc_parser::QDocParser;

fn print_doc_comments<W: Write>(dest: &mut W, text: &String, indent: usize) {
    let lines = text.split("\n");

    for line in lines {
		for _ in 0..indent {
			write!(dest, " ").unwrap();
		}

        if line.len() > 1 {
            writeln!(dest, "/// {}", line.trim());
        } else {
            writeln!(dest, "/// ");
        }
    }
}

fn main() {
    let info = QDocParser::parse_files(vec![
        env::args()
            .collect::<Vec<String>>()
            .get(1)
            .unwrap_or(&"cpp/example.cpp".to_owned()),
    ]);

    let mut file_count = 0;

    for (_path, result) in info {
        let mut func_count = 0;

        let t = result.unwrap();
        let target_name = format!("data/dummy_crate/src/file_{}.rs", file_count);
        let mut target = BufWriter::new(File::create(target_name).unwrap());

        // Find class data and output that first if we have any

        for entry in &t.0 {
            match entry.data {
                QDocItem::Class(_) => {
                    print_doc_comments(&mut target, &entry.rustdoc_text, 0);
                    break;
                }

                _ => (),
            }
        }

        writeln!(target, "pub struct Dummy{};\n", file_count).unwrap();
        writeln!(target, "impl Dummy{} {{", file_count).unwrap();

        for entry in &t.0 {
            match entry.data {
                QDocItem::Function(_) => {
                    print_doc_comments(&mut target, &entry.rustdoc_text, 4);
                    writeln!(
                        target,
                        "    pub fn func_{}() -> usize {{ {} }}",
                        func_count, func_count
                    ).unwrap();
                }

                _ => (),
            }

            func_count += 1;
        }

        writeln!(target, "}}").unwrap();

        file_count += 1;
    }

    // Generate main output

    let mut target = BufWriter::new(File::create("data/dummy_crate/src/lib.rs").unwrap());

    for i in 0..file_count {
        writeln!(target, "pub mod file_{};", i);
    }
}
