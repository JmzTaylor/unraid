// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/Theme.hpp
//       A chimera theme.
// ---------------------------------------------------------------------------------------------------------------------
#pragma once

// Includes: Stdlib
#include <map>
#include <optional>
#include <string>
#include <vector>

// Includes: Application
#include "ThemeOption.hpp"
// ---------------------------------------------------------------------------------------------------------------------

namespace chimera {
	class Theme {
		protected:

			const std::string name;
			std::map<std::string, chimera::ThemeOption> options;
			bool supported;

		public:

			// ----- Constructors -----

			Theme(std::string& name);

			// ----- Setters -----

			/**
			 * Adds a user-configurable theme option.
			 * @param option The option to add.
			 */
			void addOption(ThemeOption option);

			/**
			 * Removes a configurable theme option.
			 *
			 * @param name The name of the option to remove.
			 * @returns The removed option, if one was removed.
			 */
			std::optional<ThemeOption> removeOption(const std::string& name);

			/**
			 * Sets whether or not the theme is supported for the specified version of unraid.
			 * @param supported Whether or not the theme is supported.
			 */
			void setSupported(bool supported);

			// ----- Getters -----

			/**
			 * Gets a configurable theme option.
			 *
			 * @param name The name of the option to remove.
			 * @returns The option, if one exists.
			 */
			std::optional<ThemeOption&> getOption(const std::string& name) const;

			/**
			 * Gets a list of configurable theme options.
			 * @returns A vector of theme options.
			 */
			std::vector<std::string&> getOptionNames() const;

			/**
			 * Gets the theme name.
			 * @returns The theme name.
			 */
			std::string getName() const;

			/**
			 * Gets the theme directory.
			 * @returns The directory where the theme files are stored.
			 */
			std::string getDirectory() const;

			/**
			 * Gets whether or not the theme is supported for the specified version of unraid.
			 * @returns True if the theme is supported.
			 */
			bool isSupported();

	};
}
