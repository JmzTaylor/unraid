// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/App.hpp
//       The main application class for chimera.
// ---------------------------------------------------------------------------------------------------------------------
#pragma once

// Includes: Stdlib
#include <string>

// Includes: Library
#include <cxxopts.hpp>

// Includes: Application
#include "Unraid.hpp"
// ---------------------------------------------------------------------------------------------------------------------

namespace chimera {
	class App {
		protected:

			cxxopts::Options* opts = nullptr;

		public:

			// ----- Fields -----

			/**
			 * The parsed app options.
			 */
			cxxopts::ParseResult* options = nullptr;

			// ----- Constructor / Destructor -----

			/**
			 * Constructor.
			 *
			 * @param argc The number of arguments.
			 * @param argv The array of arguments.
			 */
			App(int argc, char** argv);

			/**
			 * Destructor.
			 */
			~App();

			// ----- Info Functions -----

			/**
			 * Show command help.
			 */
			void showHelp() const;

			/**
			 * Show the command version.
			 */
			void showVersion() const;

			// ----- Getters -----

			/**
			 * Gets the Chimera version.
			 * @return The version string.
			 */
			const std::string getVersion() const;

			/**
			 * Gets the Unraid info and settings object.
			 * This is lazily loaded.
			 *
			 * @return The Unraid info and settings object.
			 */
			Unraid& getUnraid();

	};
}
