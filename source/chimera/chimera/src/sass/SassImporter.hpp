// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/sass/SassImporter.hpp
//       An abstract class which wraps the sass importer API.
// ---------------------------------------------------------------------------------------------------------------------
#pragma once

// Includes: Stdlib
#include <string>
#include <vector>

// Includes: Library
#include <sass.h>

// Includes: Application
#include "SassImportEntry.hpp"
// ---------------------------------------------------------------------------------------------------------------------

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
			virtual void Import(const std::string& path, const std::string& parent, std::vector<chimera::sass::SassImportEntry>& files) = 0;

			// ----- Implementation -----

			/**
			 * A wrapper around the sass importer feature.
			 * https://github.com/sass/libsass/blob/master/docs/api-importer.md
			 */
			static Sass_Import_List Importer(const char* path, Sass_Importer_Entry cb, struct Sass_Compiler* compiler);

		public:

			// ----- Constructors / Destructor -----

			virtual ~SassImporter() = default;


			// ----- API -----

			/**
			 * Creates a new libsass Sass_Importer_Entry object from this.
			 * This object's lifetime must either be managed manually, or have its ownership given to libsass.
			 */
			Sass_Importer_Entry NewSass();


	};
}
