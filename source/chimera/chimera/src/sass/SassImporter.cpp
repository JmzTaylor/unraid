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

Sass_Importer_Entry SassImporter::NewSass() {
	return sass_make_importer(chimera::sass::SassImporter::Importer, 0, reinterpret_cast<void*>(this));
}

// ---------------------------------------------------------------------------------------------------------------------
// Integration:

Sass_Import_List SassImporter::Importer(const char* path, Sass_Importer_Entry cb, struct Sass_Compiler* compiler) {
	SassImporter* self = static_cast<SassImporter*>(sass_importer_get_cookie(cb));
	vector<SassImportEntry> files;

	try {
		self->Import(path, "[TODO]", files);

		// Convert the vector to a sass import list.
		Sass_Import_List import_list = sass_make_import_list(files.size());

		size_t i = 0;
		for (const auto& file : files) {
			import_list[i++] = file.NewSass();
		}

		return import_list;
	} catch (SassError& error) {
		// Pass the message along to libsass.
		Sass_Import_List import_list = sass_make_import_list(1);

		import_list[0] = sass_make_import_entry(path, 0, 0);
		sass_import_set_error(import_list[0], sass_copy_c_string(error.what()), 0, 0);

		return import_list;
	}
}
