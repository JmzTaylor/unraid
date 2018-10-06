// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/util/PathUtil.hpp
//       Various utility functions for working with unix paths.
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
