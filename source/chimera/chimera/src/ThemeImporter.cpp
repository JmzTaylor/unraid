// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/ThemeImporter.cpp
//       The libsass importer for loading theme files.
// ---------------------------------------------------------------------------------------------------------------------
// Includes: Stdlib
#include <algorithm>
#include <string>
#include <vector>

// Includes: Library
#include <fmt/format.h>

// Includes: Application
#include "sass/SassError.hpp"
#include "sass/SassImportEntry.hpp"
#include "util/PathUtil.hpp"
#include "util/StringUtil.hpp"
#include "Theme.hpp"
#include "ThemeImporter.hpp"

// Usings:
using chimera::sass::SassError;
using chimera::sass::SassImportEntry;
using chimera::util::PathUtil;
using chimera::util::StringUtil;
using chimera::Theme;
using chimera::ThemeImporter;
using std::vector;
using std::string;
// ---------------------------------------------------------------------------------------------------------------------
// Constructors / Destructors:

ThemeImporter::ThemeImporter(const Theme& theme) : theme(theme) {
}

// ---------------------------------------------------------------------------------------------------------------------
// SassImporter:

void ThemeImporter::import(const string& path, const string& parent, vector<SassImportEntry>& files) {
	if (!StringUtil::starts_with(path, "theme:")) return;

	// Get the path from the URL and normalize it.
	string file_unsafe = path.substr(6);
	string file        = PathUtil::normalize(file_unsafe);

	// Ensure that nothing shady is going on.
	if (StringUtil::starts_with(file, "..")) throw SassError(fmt::format("File to import not allowed: {}", file));

	// Find the file(s).
	vector<string> found = PathUtil::expand(path, this->theme.getDirectory());
	if (found.empty()) throw SassError(fmt::format("File to import not found or unreadable: {}", file));

	// Convert the files to import entries.
	// Add them to the import list.
	for (auto file : found) {
		files.push_back(SassImportEntry(file));
	}
}
