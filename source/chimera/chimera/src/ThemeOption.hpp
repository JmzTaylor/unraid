// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/ThemeOption.hpp
//       An option available for a chimera theme.
// ---------------------------------------------------------------------------------------------------------------------
#pragma once

// Includes: Stdlib
#include <string>

// Includes: Library
#include <sass.h>
// ---------------------------------------------------------------------------------------------------------------------
namespace chimera {
	class ThemeOption {
		protected:

			std::string name_;
			std::string default_value_;
			std::string value_;
			Sass_Tag type_;

		public:

			// ----- Setters -----

			/**
			 * Sets the option's sass variable name.
			 * @param name The variable name.
			 */
			void set_name(std::string name);

			/**
			 * Sets the option's default value.
			 * @param value The default value.
			 */
			void set_default_value(std::string value);

			/**
			 * Sets the option's value.
			 * @param value The value.
			 */
			void set_value(std::string value);

			/**
			 * Sets the option's sass variable type.
			 * @param type The variable type.
			 */
			void set_type(Sass_Tag type);

			// ----- Getters -----

			/**
			 * Gets the option's sass variable name.
			 * @return The variable name.
			 */
			const std::string& name() const;

			/**
			 * Gets the option's default value.
			 * @return The default value.
			 */
			const std::string& default_value() const;

			/**
			 * Gets the option's current value.
			 * @return The current value.
			 */
			const std::string& value() const;

			/**
			 * Gets the option's sass variable type.
			 * @return The variable type.
			 */
			Sass_Tag type() const;

			/**
			 * Generates code for setting the option inside a SCSS file.
			 * @return The generated code.
			 */
			const std::string GenerateScss() const;

			/**
			 * Generates code for setting the option inside a SASS file.
			 * @return The generated code.
			 */
			const std::string GenerateSass() const;

	};
}
