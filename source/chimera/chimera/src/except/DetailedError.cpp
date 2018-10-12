// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/sass/SassImporter.hpp
//       A class which wraps the Sass_Value error object.
// ---------------------------------------------------------------------------------------------------------------------
// Includes: Stdlib
#include <optional>
#include <map>
#include <string>
#include <stdexcept>

// Includes: Application
#include "DetailedError.hpp"

// Using:
using chimera::except::DetailedError;
using std::runtime_error;
using std::map;
using std::string;
// ---------------------------------------------------------------------------------------------------------------------
// Constructors / Destructors:

DetailedError::DetailedError(const string& what) : std::runtime_error(what), details_({}) {
}

DetailedError::DetailedError(const string& what, const std::map<std::string, std::string>& details) : std::runtime_error(what), details_(details) {
}

// ---------------------------------------------------------------------------------------------------------------------
// Getters:

const std::map<std::string, std::string>& DetailedError::details() const {
	return this->details_;
}

const std::optional<std::string> DetailedError::what_function() const {
	if (this->details_.count("function")) {
		return {this->details_.at("function")};
	}

	return {};
}
