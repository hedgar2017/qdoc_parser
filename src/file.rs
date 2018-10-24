//! 
//! The QDoc file module
//! 

use std::fmt;

use entry::QDocEntry;

/// 
/// Represents a single *.cpp file.
/// Basically, just a vector of QDoc entries.
/// 
#[derive(Debug)]
pub struct QDocFile (pub Vec<QDocEntry>);

impl fmt::Display for QDocFile {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        for (index, entry) in self.0.iter().enumerate() {
            writeln!(f, "Entry {}\n{}", index, entry);
        }
        Ok(())
    }
}
