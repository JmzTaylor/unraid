// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/App.cpp
//       The main application class for chimera.
// ---------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>

#include <sass.h>

#include "App.hpp"


// ----- Constructor / Destructor -----

chimera::App::App(int argc, char** argv) {
	this->opts = new cxxopts::Options(argv[0], "The chimera sass compiler.");

	// Informational Options:
	this->opts->add_options("info")
		("help",    "Show help information.",    cxxopts::value<bool>())
		("version", "Show version information.", cxxopts::value<bool>());

	// Sass/SCSS Options:
	this->opts->add_options("sass")
		("o,output", "Specify the output file.", cxxopts::value<std::string>())
		("m,minify", "Minify the output CSS.",   cxxopts::value<bool>());

	// Chimera Options:
	this->opts->add_options("chimera compiler")
		("unraid-version",  "Set the Unraid version variable.", cxxopts::value<std::string>())
		("unraid-theme",    "Set the Unraid theme variable.",   cxxopts::value<std::string>())
		("var",             "Set a SASS variable.",             cxxopts::value<std::vector<std::string>>());

	this->opts->add_options("chimera theme")
		("show-theme-options",   "Show the options available in the theme.",    cxxopts::value<std::string>())
		("show-theme-supported", "Show whether or not the theme is supported.", cxxopts::value<bool>());

	// Automation:
	this->opts->add_options("automation")
		("json", "Output everything as JSON.", cxxopts::value<bool>());

	// Parse.
	this->options = this->opts->parse_to_heap(argc, argv);
}

chimera::App::~App() {
	delete this->options;
	delete this->opts;
}

// ----- Info Functions -----

void chimera::App::showHelp() const {
	std::cout << this->opts->help({"info", "sass", "chimera compiler", "chimera theme"}) << std::endl;
}

void chimera::App::showVersion() const {
	std::cout
		<< "chimera " << this->getVersion() << " (libsass " << libsass_version() << ")" << std::endl
		<< std::endl
		<< "Licenses: " << URL_LICENSES << std::endl
		<< "GitHub:   " << URL_GITHUB << std::endl
		<< "GitLab:   " << URL_GITLAB << std::endl;
}

// ----- Getters -----

const std::string chimera::App::getVersion() const {
	return std::string(APP_VERSION);
}
