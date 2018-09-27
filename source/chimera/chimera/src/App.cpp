// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/app.cpp
//       The main application class for chimera.
// ---------------------------------------------------------------------------------------------------------------------
#include <cstring>

#include "App.hpp"


chimera::App::App(int argc, char** argv) {
	this->opts = new cxxopts::Options(argv[0], "the chimera sass compiler");

	// Options.
	this->opts->add_options()
		("help",    "Show help information.",    cxxopts::value<bool>())
		("version", "Show version information.", cxxopts::value<bool>());

	// Parse.
	this->options = this->opts->parse_to_heap(argc, argv);
}

chimera::App::~App() {
	delete this->options;
	delete this->opts;
}