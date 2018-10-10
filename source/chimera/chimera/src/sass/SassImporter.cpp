// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/sass/SassImporter.hpp
//       An abstract class which wraps the sass importer API.
// ---------------------------------------------------------------------------------------------------------------------
// Includes: Stdlib
#include <string>
#include <vector>

// Includes: Library
#include <sass.h>

// Includes: Application
#include "SassError.hpp"
#include "SassImportEntry.hpp"
#include "SassImporter.hpp"

// Usings:
using chimera::sass::SassError;
using chimera::sass::SassImportEntry;
using chimera::sass::SassImporter;
using std::vector;
// ---------------------------------------------------------------------------------------------------------------------
// API:

Sass_Importer_Entry SassImporter::newSass() {
	return sass_make_importer(chimera::sass::SassImporter::sass_importer, 0, reinterpret_cast<void*>(this));
}

// ---------------------------------------------------------------------------------------------------------------------
// Integration:

Sass_Import_List SassImporter::sass_importer(const char* path, Sass_Importer_Entry cb, struct Sass_Compiler* comp) {
	SassImporter* self = static_cast<SassImporter*>(sass_importer_get_cookie(cb));
	vector<SassImportEntry> files;

	try {
		self->import(path, "[TODO]", files);

		// Convert the vector to a sass import list.
		Sass_Import_List list = sass_make_import_list(files.size());

		size_t i = 0;
		for (const auto& file : files) {
			list[i++] = file.newSass();
		}

		return list;
	} catch (SassError& error) {
		// Pass the message along to libsass.
		Sass_Import_List list = sass_make_import_list(1);
		list[0] = sass_make_import_entry(path, 0, 0);
		sass_import_set_error(list[0], sass_copy_c_string(error.what()), 0, 0);
		return list;
	}
}
