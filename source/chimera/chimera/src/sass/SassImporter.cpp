// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/sass/SassImporter.hpp
//       An abstract class which wraps the sass importer API.
// ---------------------------------------------------------------------------------------------------------------------
#pragma once

#include <string>
#include <optional>

#include <sass.h>
#include <sass/functions.h>

namespace chimera::sass {
	class SassImporter {
		protected:


			// ----- API -----

			/**
			 * A virtual function for resolving imports from a path.
			 *
			 * @param parent The parent path.
			 * @param path The requested path.
			 *
			 * @returns A vector of files to import.
			 */
			virtual void import(std::string path, std::string parent, std::vector<chimera::sass::SassImport>& files) = 0;

			// ----- Implementation -----

			/**
			 * A wrapper around the sass importer feature.
			 * https://github.com/sass/libsass/blob/master/docs/api-importer.md
			 */
			Sass_Import_List sass_importer(const char* path, Sass_Importer_Entry cb, struct Sass_Compiler* comp) {
				SassImporter* self = static_cast<SassImporter*>(sass_importer_get_cookie(cb));
				std::vector<chimera::sass::SassImport> files;

				try {
					self->import(path, "TODO", files);

					// Convert the vector to a sass import list.
					Sass_Import_List list = sass_make_import_list(files.size());

					size_t i = 0;
					for (const auto& file : files) {
						list[i++] = file.toImportEntry();
					}

					return list;
				} catch (chimera::sass::SassError& error) {
					// Pass the message along to libsass.
					Sass_Import_List list = sass_make_import_list(1);
					list[0] = sass_make_import_entry(path, 0, 0);
					sass_import_set_error(list[0], sass_copy_c_string(error.what().c_str()), 0, 0);
					return list;
				}
			}

		public:

			// ----- Constructors -----

			SassImporter();


	};
}
