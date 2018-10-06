// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/ThemeCompiler.hpp
//       A wrapper for libsass used to compile chimera themes.
// ---------------------------------------------------------------------------------------------------------------------
#pragma once

#include <string>

#include <sass.h>


namespace chimera {
	class ThemeCompiler {
		protected:



		public:

			// ----- Getters -----

			/**
			 * Gets the version of the running Unraid instance.
			 * The version can be found by parsing `/var/local/emhttp/var.ini`.
			 *
			 * @return The Unraid version.
			 */
			const std::string& getUnraidVersion() const;

	};
}
