// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/util/PathUtil.hpp
//       Various utility functions for working with unix paths.
// ---------------------------------------------------------------------------------------------------------------------
#pragma once

// Includes: Stdlib
#include <string>
#include <vector>
// ---------------------------------------------------------------------------------------------------------------------

namespace chimera::util {
	class PathUtil {
	public:

		// ----- Normalization -----

		/**
		 * Normalizes a path without resolving any links.
		 *
		 * @param path The path to normalize.
		 * @returns The normalized path.
		 */
		static std::string normalize(const std::string& path);


		// ----- Working Directory ------

		/**
		 * Gets the working directory of the current process.
		 * @returns The working directory.
		 *
		 * @throws std::ios_base::failure
		 */
		static std::string workdir();

		/**
		 * Changes the working directory of the current process.
		 * @param directory The new working directory.
		 *
		 * @throws chimera::except::DetailedError
		 */
		static void chdir(const std::string& directory);

		// ----- Expansion -----

		/**
		 * Uses glob(3) to expand a path.
		 *
		 * @param pattern The pattern to expand.
		 *
		 * @returns A vector of matching files.
		 *
		 * @throws chimera::except::DetailedError
		 */
		static std::vector<std::string> expand(const std::string& pattern);

		/**
		 * Uses glob(3) to expand a path.
		 *
		 * @param pattern The pattern to expand.
		 * @param results The vector to place the results into.
		 *
		 * @throws chimera::except::DetailedError
		 */
		static void expand(const std::string& pattern, std::vector<std::string>& results);

		/**
		 * Uses glob(3) to expand a path.
		 *
		 * @param pattern The pattern to expand.
		 * @param directory The relative directory.
		 *
		 * @returns A vector of matching files.
		 *
		 * @throws chimera::except::DetailedError
		 */
		static std::vector<std::string> expand(const std::string& pattern, const std::string& directory);

		/**
		 * Uses glob(3) to expand a path.
		 *
		 * @param pattern The pattern to expand.
		 * @param directory The relative directory.
		 * @param results The vector to place the results into.
		 *
		 * @throws chimera::except::DetailedError
		 */
		static void expand(const std::string& pattern, const std::string& directory, std::vector<std::string>& results);

		/**
		 * Uses glob(3) to expand a path.
		 *
		 * @param pattern The pattern to expand.
		 * @param directory The relative directory.
		 * @param glob_flags Additional flags to pass to glob(3).
		 *
		 * @returns A vector of matching files.
		 *
		 * @throws chimera::except::DetailedError
		 */
		static std::vector<std::string> expand(const std::string& pattern, const std::string& directory, int glob_flags);

		/**
		 * Uses glob(3) to expand a path.
		 *
		 * @param pattern The pattern to expand.
		 * @param directory The relative directory.
		 * @param glob_flags Additional flags to pass to glob(3).
		 * @param results The vector to place the results into.
		 *
		 * @throws chimera::except::DetailedError
		 */
		static void expand(const std::string& pattern, const std::string& directory, int glob_flags, std::vector<std::string>& results);

		/**
		 * Uses wordexp(3) to expand a path.
		 *
		 * @param pattern The pattern to expand.
		 *
		 * @returns A vector of matching files.
		 *
		 * @throws chimera::except::DetailedError
		 */
		static std::vector<std::string> expand_shell(const std::string& pattern);

		/**
		 * Uses wordexp(3) to expand a path.
		 *
		 * @param pattern The pattern to expand.
		 * @param results The vector to place the results into.
		 *
		 * @throws chimera::except::DetailedError
		 */
		static void expand_shell(const std::string& pattern, std::vector<std::string>& results);

		/**
		 * Uses wordexp(3) to expand a path.
		 *
		 * @param pattern The pattern to expand.
		 * @param directory The relative directory.
		 *
		 * @returns A vector of matching files.
		 *
		 * @throws chimera::except::DetailedError
		 */
		static std::vector<std::string> expand_shell(const std::string& pattern, const std::string& directory);

		/**
		 * Uses wordexp(3) to expand a path.
		 *
		 * FIXME: Doesn't filter out failed matches properly.
		 *        Try "\\$TEST". It should return an empty vector, but it doesn't.
		 *
		 * @param pattern The pattern to expand.
		 * @param directory The relative directory.
		 * @param results The vector to place the results into.
		 *
		 * @throws chimera::except::DetailedError
		 */
		static void expand_shell(const std::string& pattern, const std::string& directory, std::vector<std::string>& results);

	};
}
