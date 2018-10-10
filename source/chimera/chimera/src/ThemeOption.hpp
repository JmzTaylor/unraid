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

			std::string name;
			std::string valueDefault;
			std::string value;
			Sass_Tag type;

		public:

			// ----- Setters -----

			/**
			 * Sets the option's sass variable name.
			 * @param name The variable name.
			 */
			void setName(std::string name);

			/**
			 * Sets the option's default value.
			 * @param value The default value.
			 */
			void setDefault(std::string value);

			/**
			 * Sets the option's value.
			 * @param value The value.
			 */
			void setValue(std::string value);

			/**
			 * Sets the option's sass variable type.
			 * @param type The variable type.
			 */
			void setType(Sass_Tag type);

			// ----- Getters -----

			/**
			 * Gets the option's sass variable name.
			 * @return The variable name.
			 */
			const std::string& getName() const;

			/**
			 * Gets the option's default value.
			 * @return The default value.
			 */
			const std::string& getDefault() const;

			/**
			 * Gets the option's current value.
			 * @return The current value.
			 */
			const std::string& getValue() const;

			/**
			 * Gets the option's sass variable type.
			 * @return The variable type.
			 */
			Sass_Tag getType() const;

			/**
			 * Generates code for setting the option inside a SCSS file.
			 */
			const std::string toScss() const;

	};
}
