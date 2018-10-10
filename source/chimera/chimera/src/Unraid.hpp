// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/Unraid.hpp
//       A class for reading (and maybe writing) Unraid settings.
// ---------------------------------------------------------------------------------------------------------------------
#pragma once

// Includes: Stdlib
#include <string>
#include <vector>

// Includes: Library
#include <sass.h>
// ---------------------------------------------------------------------------------------------------------------------
namespace chimera {
	class Unraid {
		protected:



		public:

			// ----- Getters -----

			/**
			 * Gets the version of the running Unraid instance.
			 * The version can be found by parsing `/var/local/emhttp/var.ini`.
			 *
			 * @return The Unraid version.
			 */
			const std::string& getVersion() const;

			/**
			 * Gets the active Dynamix theme.
			 * The theme can be found by parsing `/boot/config/plugins/dynamix/dynamix.cfg`.
			 *
			 * @return The active Dynamix theme.
			 */
			const std::string& getDynamixTheme();

			/**
			 * Gets the Dynamix theme directory.
			 * This should be `/usr/local/emhttp/plugins/dynamix/styles`.
			 *
			 * @return The Dynamix theme directory.
			 */
			const std::string& getDynamixThemeDirectory() const;

			/**
			 * Gets a list of Dynamix themes.
			 * This should be `/usr/local/emhttp/plugins/dynamix/styles/dynamix-*.css`.
			 *
			 * @return A list of available Dynamix themes.
			 */
			const std::vector<std::string>& getDynamixThemeList() const;


	};
}
