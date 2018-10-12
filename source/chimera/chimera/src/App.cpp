// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/App.cpp
//       The main application class for chimera.
// ---------------------------------------------------------------------------------------------------------------------
// Includes: Stdlib
#include <iostream>
#include <string>

// Includes: Library
#include <fmt/format.h>
#include <sass.h>

// Includes: Application
#include "App.hpp"
#include "Compiler.hpp"

// Usings:
using chimera::App;
using std::cout;
using std::string;
using std::vector;
// ---------------------------------------------------------------------------------------------------------------------
// Constructors / Destructors:

App::App(int argc, char** argv) {
	this->opts = new cxxopts::Options(argv[0], "The chimera sass compiler.");

	// Informational Options:
	this->opts->add_options("info")
		("help",    "Show help information.",                                   cxxopts::value<bool>())
		("version", "Show version information.",                                cxxopts::value<bool>())
		("show-theme-options",   "Show the options available in the theme.",    cxxopts::value<bool>())
		("show-theme-supported", "Show whether or not the theme is supported.", cxxopts::value<bool>());

	// Sass/SCSS Options:
	this->opts->add_options("sass")
		("o,output",    "Specify the output file.",            cxxopts::value<string>())
		("m,minify",    "Minify the output.",                  cxxopts::value<bool>())
		("s,sourcemap", "Include a sourcemap in the output.",  cxxopts::value<bool>());

	// Chimera Options:
	this->opts->add_options("chimera compiler")
		("unraid-version",  "Set the Unraid version variable.",         cxxopts::value<string>())
		("unraid-theme",    "Set the Unraid theme variable.",           cxxopts::value<string>())
		("var",             "Set a SASS variable in key:value format.", cxxopts::value<vector<string>>());

	this->opts->add_options("chimera theme")
		("theme",           "Specify the theme directory.",          cxxopts::value<string>())
		("theme-file",      "Specify the theme file.",               cxxopts::value<string>()->default_value("theme.scss"))
		("theme-resources", "Specify the theme resource directory.", cxxopts::value<string>());

	// Automation:
	this->opts->add_options("automation")
		("json", "Output everything as JSON.", cxxopts::value<bool>());

	// Parse.
	this->options = this->opts->parse_to_heap(argc, argv);
}

App::~App() {
	delete this->options;
	delete this->opts;
}

// ---------------------------------------------------------------------------------------------------------------------
// Info Functions:

void App::ShowHelp() const {
	std::cout << this->opts->help({"info", "sass", "chimera compiler", "chimera theme"}) << std::endl;
}

void App::ShowVersion() const {
	cout << fmt::format("{} {} (libsass {})\n\n", "chimera", this->version(), libsass_version())
		<< fmt::format("Licenses: {}\n", URL_LICENSES)
		<< fmt::format("GitHub:   {}\n", URL_GITHUB)
		<< fmt::format("GitLab:   {}\n", URL_GITLAB);
}

// ---------------------------------------------------------------------------------------------------------------------
// Getters:

const string App::version() const {
	return string(APP_VERSION);
}
