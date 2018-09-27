// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/main.cpp
//       The entry point for chimera.
// ---------------------------------------------------------------------------------------------------------------------
#include "App.hpp"


int main(int argc, char** argv) {
	chimera::App app(argc, argv);

	// -----------------------
	// Argument: --help
	// -----------------------
	if (app.options->count("help")) {
		app.showHelp();
		return 0;
	}

	// -----------------------
	// Argument: --version
	// -----------------------
	if (app.options->count("version")) {
		app.showVersion();
		return 0;
	}

	return 0;
}
