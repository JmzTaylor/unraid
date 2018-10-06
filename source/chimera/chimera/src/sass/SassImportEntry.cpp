// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/sass/SassImporterEntry.hpp
//       An abstract class which wraps the sass importer API.
// ---------------------------------------------------------------------------------------------------------------------
// Includes: Stdlib
#include <iostream>
#include <optional>
#include <string>

// Includes: Library
#include <sass.h>

// Includes: Application
#include "SassImportEntry.hpp"

// Using:
using chimera::sass::SassImportEntry;
using std::istream;
using std::optional;
using std::string;
// ---------------------------------------------------------------------------------------------------------------------
// Constructors / Destructors:

SassImportEntry::SassImportEntry(const string& file) : file(file) {
	this->contents = std::nullopt;
}

SassImportEntry::SassImportEntry(const string& file, const string& contents) : file(file) {
	this->contents = std::make_optional(contents);
}

SassImportEntry::SassImportEntry(const string& file, istream& stream) : file(file) {
	this->contents = std::make_optional(string(std::istreambuf_iterator<char>(stream), {}));
}

// ---------------------------------------------------------------------------------------------------------------------
// Getters:

const string& SassImportEntry::getFile() const {
	return this->file;
}

const optional<const string> SassImportEntry::getContents() const {
	return this->contents;
}

// ---------------------------------------------------------------------------------------------------------------------
// API:

Sass_Import_Entry SassImportEntry::newSass() const {
	return sass_make_import_entry(
		sass_copy_c_string(this->file.c_str()),
		this->contents ? sass_copy_c_string(this->contents->c_str()) : 0,
		0
	);
}
