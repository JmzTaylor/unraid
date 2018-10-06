// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/sass/SassImporter.hpp
//       A class which wraps the Sass_Value error object.
// ---------------------------------------------------------------------------------------------------------------------
// Includes: Stdlib
#include <string>
#include <stdexcept>

// Includes: Library
#include <sass.h>

// Includes: Application
#include "SassError.hpp"

// Using:
using chimera::sass::SassError;
using std::string;
// ---------------------------------------------------------------------------------------------------------------------
// Constructors / Destructors:

SassError::SassError(const string& what) : std::runtime_error(what) {
}

// ---------------------------------------------------------------------------------------------------------------------
// API:

union Sass_Value* SassError::newSass() const {
	return sass_make_error(sass_copy_c_string(this->what()));
}
