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

SassImportEntry::SassImportEntry(const string& file) : file_(file) {
	this->contents_ = {};
}

SassImportEntry::SassImportEntry(const string& file, const string& contents) : file_(file) {
	this->contents_ = contents;
}

SassImportEntry::SassImportEntry(const string& file, istream& stream) : file_(file) {
	this->contents_ = string(std::istreambuf_iterator<char>(stream), {});
}

// ---------------------------------------------------------------------------------------------------------------------
// Getters:

const string& SassImportEntry::file() const {
	return this->file_;
}

const optional<const string> SassImportEntry::contents() const {
	return this->contents_;
}

// ---------------------------------------------------------------------------------------------------------------------
// API:

Sass_Import_Entry SassImportEntry::NewSass() const {
	return sass_make_import_entry(
		sass_copy_c_string(this->file_.c_str()),
		this->contents_ ? sass_copy_c_string(this->contents_->c_str()) : 0,
		0
	);
}
