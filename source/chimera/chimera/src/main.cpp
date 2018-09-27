// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/compiler.cpp
//       TODO docs
// ---------------------------------------------------------------------------------------------------------------------
#include "App.hpp"

int main(int argc, char** argv) {
	chimera::App app(argc, argv);

	// -----------------------
	// Argument: --help
	// -----------------------
	if (app.options->count("help")) {
		std::cout << "TODO: Help" << std::endl;
		return 0;
	}

	// -----------------------
	// Argument: --version
	// -----------------------
	if (app.options->count("version")) {
		std::cout
			<< "chimera " << APP_VERSION << " (libsass " << libsass_version() << ")" << std::endl
			<< std::endl
			<< "Licenses: " << URL_LICENSES << std::endl
			<< "GitHub:   " << URL_GITHUB << std::endl
			<< "GitLab:   " << URL_GITLAB << std::endl;
		return 0;
	}

	return 0;
}
