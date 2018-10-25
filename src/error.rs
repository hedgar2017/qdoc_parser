//!
//! The error module
//!

use std::io;

#[derive(Debug, Fail)]
pub enum Error {
    #[fail(display = "File reading error: {}", _0)]
    Read(io::Error),
    #[fail(display = "File parsing error:\n{}", _0)]
    Parse(String),
}

impl From<io::Error> for Error {
    fn from(error: io::Error) -> Self {
        Error::Read(error)
    }
}
