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
pub struct QDocEntry {
    /// If this is set it means that the doc entry is atteached to a cpp function
    pub target_cpp_function: Option<String>,
    /// This has the original QDoc text in it
    pub qdoc_text: String,
    /// This has the RustDoc translated/converted text in it
    pub rustdoc_text: String,
}

impl fmt::Display for QDocEntry {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        writeln!(f, "QDoc original text:");
        for line in self.qdoc_text.trim().lines() {
            writeln!(f, "{}", line)?;
        }
        writeln!(f, "Rustdoc translated text:");
        for line in self.rustdoc_text.trim().lines() {
            writeln!(f, "{}", line)?;
        }
        Ok(())
    }
}
