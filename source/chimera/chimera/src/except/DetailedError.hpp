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
#include <map>
#include <optional>
#include <string>
#include <stdexcept>
// ---------------------------------------------------------------------------------------------------------------------

namespace chimera::except {
	class DetailedError : public std::runtime_error {
		protected:

			const std::map<std::string, std::string> details_;

		public:

			// ----- Constructors / Destructors -----

			/**
			 * Creates an error.
			 *
			 * @param function The C function name.
			 * @param what The error message.
			 */
			DetailedError(const std::string& what);

			/**
			 * Creates an error.
			 *
			 * @param what The error message.
			 * @param details Additional information.
			 */
			DetailedError(const std::string& what, const std::map<std::string, std::string>& details);

			// ----- Getters -----

			/**
			 * Gets the name of the function that caused the error.
			 * @return The function name.
			 */
			const std::optional<std::string> what_function() const;

			/**
			 * Gets additional details.
			 * @return A map<string,string> of additional details.
			 */
			const std::map<std::string, std::string>& details() const;

	};
}
