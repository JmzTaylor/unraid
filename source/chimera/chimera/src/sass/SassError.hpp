// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/sass/SassError.hpp
//       A class which wraps the Sass_Value error object.
// ---------------------------------------------------------------------------------------------------------------------
#pragma once

// Includes: Stdlib
#include <string>
#include <stdexcept>

// Includes: Library
#include <sass.h>
// ---------------------------------------------------------------------------------------------------------------------

namespace chimera::sass {
	class SassError : public std::runtime_error {
		public:

			// ----- Constructors / Destructors -----

			/**
			 * Creates a libsass error.
			 *
			 * @param what The error message.
			 */
			SassError(const std::string& what);

			// ----- API -----

			/**
			 * Creates a new libsass Sass_Value object from this.
			 * This object's lifetime must either be managed manually, or have its ownership given to libsass.
			 */
			union Sass_Value* NewSass() const;

	};
}
