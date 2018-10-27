//!
//! The QDoc entry module
//!

use std::{
    fmt,
    collections::HashMap,
};

#[derive(Debug)]
pub struct QDocEnum {
    pub name: String,
    pub data: HashMap<String, String>,
}

#[derive(Debug)]
pub enum QDocItem {
    Undefined,
    Class(String),
    Function(String),
    Property(String),
    Variable(String),
    Enum(QDocEnum),
}

///
/// This is a QDoc entry that represents one section of the QDoc
/// mark up (whatever comes between /*! ... */)" along with its
/// translation to rustdoc and the name of the C++ function if
/// it is attached to one.
///
#[derive(Debug)]
pub struct QDocEntry {
    pub module: Option<String>,
    pub brief: Option<String>,
    pub data: QDocItem,
    pub qdoc_text: String,
    pub rustdoc_text: String,
}

impl QDocEntry {
    pub fn rustdoc(&self) -> String {
        let mut lines = self.rustdoc_text.lines().map(|line| line.trim()).collect::<Vec<&str>>();
        lines.dedup();
        lines.join("\n")
    }
}

impl Default for QDocEntry {
    fn default() -> Self {
        QDocEntry {
            module: None,
            brief: None,
            data: QDocItem::Undefined,
            qdoc_text: String::new(),
            rustdoc_text: String::new(),
        }
    }
}

impl fmt::Display for QDocEntry {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        use QDocItem::*;

        if let Some(ref module) = self.module {
            writeln!(f, "Module: {}", module);
        }
        if let Some(ref brief) = self.brief {
            writeln!(f, "Brief: {}", brief);
        }
        let _ = match self.data {
            Class(ref value) => writeln!(f, "Class: {}", value),
            Function(ref value) => writeln!(f, "Function: {}", value),
            Property(ref value) => writeln!(f, "Property: {}", value),
            Variable(ref value) => writeln!(f, "Variable: {}", value),
            Enum(ref value) => {
                writeln!(f, "Enum: {}", value.name);
                for (key, description) in value.data.iter() {
                    writeln!(f, "      {}: {}", key, description);
                }
                Ok(())
            },
            _ => Ok(()),
        };
        writeln!(f, "\nQDoc:");
        for line in self.qdoc_text.lines() {
            writeln!(f, "{}", line)?;
        }
        writeln!(f, "\nRustdoc:\n{}",  self.rustdoc());
        Ok(())
    }
}
