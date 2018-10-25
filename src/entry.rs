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
    /// If this is set it means that the doc entry is attached to a cpp class
    pub class_name: Option<String>,
    /// If this is set it means that the doc entry is attached to a cpp function
    pub target_cpp_function: Option<String>,
    /// This has the original QDoc text in it
    pub qdoc_text: String,
    /// This has the RustDoc translated/converted text in it
    pub rustdoc_text: String,
}

impl fmt::Display for QDocEntry {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        if let Some(ref class) = self.class_name {
            writeln!(f, "Class: {}", class);
        }
        if let Some(ref function) = self.target_cpp_function {
            writeln!(f, "Function: {}", function);
        }
        writeln!(f, "\nQDoc:");
        for line in self.qdoc_text.lines() {
            writeln!(f, "{}", line)?;
        }
        writeln!(f, "\nRustdoc:");
        for line in self.rustdoc_text.lines() {
            writeln!(f, "{}", line)?;
        }
        Ok(())
    }
}
