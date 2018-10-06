// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/sass/SassError.hpp
//       A class which wraps the Sass_Value error object.
// ---------------------------------------------------------------------------------------------------------------------
#pragma once

#include <string>
#include <stdexcept>

#include <sass.h>
// ---------------------------------------------------------------------------------------------------------------------
namespace chimera::util::PathUtil {

	/**
	 * Normalizes a path without resolving any links.
	 * 
	 * @param path The path to normalize.
	 * @returns The normalized path.
	 */
	std::string normalize(const std::string& path);

}
