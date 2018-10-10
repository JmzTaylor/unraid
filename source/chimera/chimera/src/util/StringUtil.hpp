// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/util/StringUtil.hpp
//       Various utility functions for working with strings.
// ---------------------------------------------------------------------------------------------------------------------
#pragma once

// Includes: Stdlib
#include <numeric>
#include <string>
#include <vector>
// ---------------------------------------------------------------------------------------------------------------------

namespace chimera::util {
	class StringUtil {
	public:

		/**
		 * Splits a string into a list or vector.
		 *
		 * @param str The string to split.
		 * @param delimiter The delimiter.
		 *
		 * @returns The string as a number of items in a list.
		 */
		template <template <class, class> class C>
		static C<std::string, std::allocator<std::string> > split(const std::string& str, const std::string& delimiter);

		/**
		 * Joins a list or vector into a string.
		 *
		 * @param items The items to join.
		 * @param delimiter The delimiter.
		 *
		 * @returns The joined strings.
		 */
		template <template <class, class> class C>
		static std::string join(C<std::string, std::allocator<std::string> >& items, const std::string& delimiter);

	};
}

// ---------------------------------------------------------------------------------------------------------------------
// Templates, Yay...

template <template <class, class> class C>
C<std::string, std::allocator<std::string>> chimera::util::StringUtil::split(const std::string& str, const std::string& delimiter) {
	const size_t delimiter_length = delimiter.length();

	C<std::string, std::allocator<std::string>> components;
	size_t offset = 0;
	size_t last_offset = 0;

	// Find components and add them to the list.
	while ((offset = str.find(delimiter, offset)) != std::string::npos) {
		components.push_back(str.substr(last_offset, (offset - last_offset)));
		offset += delimiter_length;
		last_offset = offset;
	}

	// Add final component to list.
	components.push_back(str.substr(last_offset));

	return components;
}


template <template <class, class> class C>
std::string chimera::util::StringUtil::join(C<std::string, std::allocator<std::string>>& items, const std::string& delimiter) {
	// Calculate length.
	size_t length = 0;
	for (auto& item : items) {
		length += item.length() + delimiter.length();
	}

	// Create string object.
	std::string str;
	str.reserve(length);

	// Append string object.
	for (auto& item : items) {
		if (str.empty()) {
			str.append(item);
		} else {
			str.append(delimiter);
			str.append(item);
		}
	}

	return str;
}
