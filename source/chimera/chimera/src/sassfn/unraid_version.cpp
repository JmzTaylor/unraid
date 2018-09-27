// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/sassfn/unraid_version.cpp
//       Binding and implementation of the `unraid-version()` sass function.
// ---------------------------------------------------------------------------------------------------------------------
#pragma once
#include <sass.h>
#include "../Theme.hpp"

namespace sassfn {

	// Signature:
	// unraid-version($compare: null)
	union Sass_Value* call_unraid_version(const union Sass_Value* args, Sass_Function_Entry cb, struct Sass_Compiler* compiler) {
		union Sass_Value* arg_compare = sass_list_get_value(args, 0);

		Theme* theme = static_cast<Theme*>(sass_function_get_cookie(cb));
		std::string &version = theme->getUnraid()->getVersion();

		// Overload: unraid-version()
		// Returns the Unraid version.
		if (sass_value_is_null(arg_compare)) {
			return sass_make_string(version.c_str());
		}

		// Overload: unraid-version(string $compare)
		// Compares the Unraid version with a semver pattern.
		if (sass_value_is_string(arg_compare)) {
			// TODO
			std::cout << sass_string_get_value(arg_compare) << std::endl;
		}

		// Unknown.
		return sass_make_error("argument `$compare` of `unraid-version($compare)` must be a string");
	}

}
