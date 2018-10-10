// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/Compiler.hpp
//       A wrapper for libsass used to compile chimera themes.
// ---------------------------------------------------------------------------------------------------------------------
#pragma once

// Includes: Stdlib
#include <string>
#include <optional>

// Includes: Library
#include <sass.h>

// Includes: Application
#include "Theme.hpp"
//#include "ThemeImporter.hpp"
// ---------------------------------------------------------------------------------------------------------------------

namespace chimera {
	class Compiler {
		protected:

			std::optional<struct Sass_Options*> options;
			std::optional<struct Sass_Data_Context*> data_context;
			const chimera::Theme& theme;


		public:

			// ----- Constructors -----

			Compiler(chimera::Theme& theme);

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



	};
}
