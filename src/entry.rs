//!
//! The QDoc entry module
//!

use std::{collections::HashMap, fmt};

#[derive(Debug)]
pub struct QDocEnum {
    pub name: String,
    pub description: String,
    pub data: HashMap<String, String>,
}

#[derive(Debug)]
pub enum QDocItem {
    Undefined,
    Class(String),
    Struct(String),
    Function(String),
    Macro(String),
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
    pub namespace: Option<String>,
    pub title: Option<String>,
    pub brief: Option<String>,
    pub data: QDocItem,
    pub qdoc_text: String,
    pub rustdoc_elements: Vec<String>,
}

impl QDocEntry {
    pub fn formatted_rustdoc(&self) -> String {
        let text = self.rustdoc_elements.join(" ");
        let mut lines = text.lines().map(|line| line.trim()).collect::<Vec<&str>>();
        lines.dedup();
        lines.join("\n")
    }
}

impl Default for QDocEntry {
    fn default() -> Self {
        QDocEntry {
            module: None,
            namespace: None,
            title: None,
            brief: None,
            data: QDocItem::Undefined,
            qdoc_text: String::new(),
            rustdoc_elements: Vec::new(),
        }
    }
}

impl fmt::Display for QDocEntry {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        use QDocItem::*;

        if let Some(ref module) = self.module {
            writeln!(f, "Module: {}", module);
        }
        if let Some(ref namespace) = self.namespace {
            writeln!(f, "Namespace: {}", namespace);
        }
        if let Some(ref title) = self.title {
            writeln!(f, "Title: {}", title);
        }
        if let Some(ref brief) = self.brief {
            writeln!(f, "Brief: {}", brief);
        }
        let _ = match self.data {
            Class(ref value) => writeln!(f, "Class: {}", value),
            Struct(ref value) => writeln!(f, "Struct: {}", value),
            Function(ref value) => writeln!(f, "Function: {}", value),
            Macro(ref value) => writeln!(f, "Macro: {}", value),
            Property(ref value) => writeln!(f, "Property: {}", value),
            Variable(ref value) => writeln!(f, "Variable: {}", value),
            Enum(ref value) => {
                writeln!(f, "Enum: {}", value.name);
                writeln!(f, "Description: {}", value.description);
                for (key, description) in value.data.iter() {
                    writeln!(f, "      {}: {}", key, description);
                }
                Ok(())
            }
            _ => Ok(()),
        };
        writeln!(f, "\nQDoc:");
        for line in self.qdoc_text.lines() {
            writeln!(f, "{}", line)?;
        }
        writeln!(f, "\nRustdoc:\n{}", self.formatted_rustdoc());
        Ok(())
    }
}
