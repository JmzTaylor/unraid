// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/SassImporter.hpp
//       The libsass importer for loading theme files.
// ---------------------------------------------------------------------------------------------------------------------
#pragma once

#include <string>
#include <optional>

#include <sass.h>
#include <sass/functions.h>

namespace chimera {
	class SassImporter {
		protected:



		public:

			// ----- Constructors -----

			SassImporter(std::string& path);

			// ----- Setters -----

			/**
			 * Sets the compiler option for minifying output CSS.
			 * Minified output does not contain comments or unnecessary whitespace.
			 *
			 * @param minify Whether or not minification is enabled.
			 */
			void setOptionMinify(bool minify);

			/**
			 * Sets the compiler option for embedding sourcemaps.
			 * @param sourcemaps Whether or not sourcemaps are enabled.
			 */
			bool setOptionSourcemaps(bool sourcemaps);

			// ----- Getters -----

			/**
			 * Gets the compiler option for minifying output CSS.
			 * Minified output does not contain comments or unnecessary whitespace.
			 *
			 * @return Whether or not minification is enabled.
			 */
			bool getOptionMinify() const;

			/**
			 * Gets the compiler option for embedding sourcemaps.
			 * @return Whether or not sourcemaps are enabled.
			 */
			bool getOptionSourcemaps() const;

			Sass_Import_List sass_importer(const char* path, Sass_Importer_Entry cb, struct Sass_Compiler* comp) {
				SassImporter* self = static_cast<SassImporter*>(sass_importer_get_cookie(cb));

			}

	};
}
