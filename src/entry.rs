//!
//! The QDoc entry module
//!

use std::fmt;

///
/// This is a QDoc entry that represents one section of the QDoc
/// mark up (whatever comes between /*! ... */)" along with its
/// translation to rustdoc and the name of the C++ function if
/// it is attached to one.
///
#[derive(Debug)]
pub struct QDocEntry {
    pub class: Option<String>,
    pub brief: Option<String>,
    pub function: Option<String>,

    pub qdoc_text: String,
    pub rustdoc_text: String,
}

impl fmt::Display for QDocEntry {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        if let Some(ref class) = self.class {
            writeln!(f, "Class: {}", class);
        }
        if let Some(ref brief) = self.brief {
            writeln!(f, "Brief: {}", brief);
        }
        if let Some(ref function) = self.function {
            writeln!(f, "Function: {}", function);
        }
        writeln!(f, "\nQDoc:");
        for line in self.qdoc_text.lines() {
            writeln!(f, "{}", line)?;
        }
        writeln!(f, "\nRustdoc:");
        writeln!(f, "{}", self.rustdoc_text)?;
        Ok(())
    }
}
