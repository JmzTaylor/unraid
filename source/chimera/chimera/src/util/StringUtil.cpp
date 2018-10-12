// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/path/StringUtil.hpp
//       Various utility functions for working with strings.
// ---------------------------------------------------------------------------------------------------------------------
// Includes: Stdlib
#include <string>

// Includes: Application
#include "StringUtil.hpp"

// Usings:
using chimera::util::StringUtil;
using std::string;
// ---------------------------------------------------------------------------------------------------------------------
// Comparision Functions:

bool StringUtil::starts_with(const std::string& str, const std::string prefix) {
	return str.compare(0, prefix.length(), prefix) == 0;
}

bool StringUtil::ends_with(const std::string& str, const std::string suffix) {
	size_t str_length    = str.length();
	size_t suffix_length = suffix.length();

	if (suffix_length > str_length) return false;
	return str.compare(str_length - suffix_length, suffix_length, suffix) == 0;
}
