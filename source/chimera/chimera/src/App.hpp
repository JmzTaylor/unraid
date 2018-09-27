// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/App.hpp
//       The main application class for chimera.
// ---------------------------------------------------------------------------------------------------------------------
#pragma once
#include <cxxopts.hpp>
#include <sass.h>

namespace chimera {
	class App {
		protected:

			cxxopts::Options* opts = nullptr;

		public:

			/**
			 * The parsed app options.
			 */
			cxxopts::ParseResult* options = nullptr;

			/**
			 * Constructor.
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
			void show_help();

			/**
			 * Show the command version.
			 */
			void show_version();

	};
}
