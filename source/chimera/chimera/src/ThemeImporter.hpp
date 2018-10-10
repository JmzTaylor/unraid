// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/ThemeImporter.hpp
//       The libsass importer for loading theme files.
// ---------------------------------------------------------------------------------------------------------------------
#pragma once

// Includes: Stdlib
#include <string>
#include <vector>

// Includes: Library
#include <sass.h>

// Includes: Application
#include "sass/SassError.hpp"
#include "sass/SassImporter.hpp"
#include "util/PathUtil.hpp"

// Usings:
using chimera::sass::SassImportEntry;
using std::string;
using std::vector;
// ---------------------------------------------------------------------------------------------------------------------

namespace chimera {
	class ThemeImporter : public SassImporter {
		protected:

			// TODO: split out in .cpp file.
			virtual void import(const string& path, const string& parent, vector<cSassImportEntry>& files) {
				if (!path.starts_with("theme:")) return;

				// Get the path from the URL and normalize it.
				string file_unsafe = path.substr(6);
				string file        = PathUtils.normalize(file_unsafe);

				// Ensure that nothing shady is going on.
				if (file.starts_with("..")) throw SassError("the file '" + file + "' could not be imported");

				// Load the file(s).
				
				// TODO: Load theme importer files.
				// TODO: Figure out how to glob with C++.
			}

		public:

			// ----- Constructors / Destructors -----

			ThemeImporter(const theme& theme);

	};
}
