// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/path/PathUtil.hpp
//       Various utility functions for working with unix paths.
// ---------------------------------------------------------------------------------------------------------------------
// Includes: Stdlib
#include <cerrno>
#include <cstring>
#include <ios>
#include <list>
#include <string>
#include <vector>

#include <glob.h>
#include <unistd.h>
#include <wordexp.h>

// Includes: Library
#include <fmt/format.h>

// Includes: Application
#include "../except/DetailedError.hpp"
#include "PathUtil.hpp"
#include "StringUtil.hpp"

// Usings:
using chimera::except::DetailedError;
using chimera::util::PathUtil;
using chimera::util::StringUtil;
using std::bad_alloc;
using std::list;
using std::next;
using std::prev;
using std::string;
using std::vector;
// ---------------------------------------------------------------------------------------------------------------------
// Normalization:
using std::runtime_error;
string PathUtil::normalize(const string& path) {
	list<string> components = StringUtil::split<list>(path, "/");

	// Normalize path components.
	for (auto it = components.begin(); it != components.end(); ++it) {
		if ((*it).empty()) {
			components.erase(it);
			continue;
		}

		if (*it == ".") {
			components.erase(it);
			continue;
		}

		if (*it == ".." && it != components.begin() && *(prev(it)) != "..") {
			components.erase(it--);
			components.erase(it);
		}
	}

	// Rebuild path from components.
	return StringUtil::join<list>(components, "/");
}

// ---------------------------------------------------------------------------------------------------------------------
// Working Directory:

string PathUtil::workdir() {
	size_t buffer_size = 4096;
	char* buffer = new char[buffer_size];

	// Attempt to use getcwd with the buffer.
	call_getcwd: {

		if (getcwd(buffer, buffer_size) == NULL) {
			switch (errno) {
				case ERANGE:
					// We need to try again with a bigger buffer.
					delete[] buffer;
					buffer = new char[buffer_size *= 2];
					goto call_getcwd;

				default:
					throw DetailedError(strerror(errno), {
						{"function", "getcwd()"}
					});
			}
		}
	}

	// Cleanup and return.
	string result = string(buffer);
	delete[] buffer;
	return result;
}

void PathUtil::chdir(const string& directory) {
	int status = ::chdir(directory.c_str());
	if (status != 0) {
		throw DetailedError(strerror(errno), {
			{"function", "chdir()"},
			{"path",     directory}
		});
	}
}

// ---------------------------------------------------------------------------------------------------------------------
// Expansion: wordexp(3)

vector<string> PathUtil::expand_shell(const string& pattern) {
	return PathUtil::expand_shell(pattern, PathUtil::workdir());
}

void PathUtil::expand_shell(const string& pattern, vector<string>& results) {
	PathUtil::expand_shell(pattern, PathUtil::workdir(), results);
}

vector<string> PathUtil::expand_shell(const string& pattern, const string& directory) {
	vector<string> results;
	PathUtil::expand_shell(pattern, directory, results);
	return results;
}

void PathUtil::expand_shell(const string& pattern, const string& directory, vector<string>& results) {
	string cwd = PathUtil::workdir();
	wordexp_t exp;

	// Change directory and run wordexp.
	PathUtil::chdir(directory);
	int status = wordexp(pattern.c_str(), &exp, WRDE_NOCMD);
	PathUtil::chdir(cwd);

	// Handle status.
	switch (status) {
		case 0:
			break;

		case WRDE_BADCHAR:
		case WRDE_BADVAL:
		case WRDE_SYNTAX:
		case WRDE_CMDSUB:
			throw DetailedError(fmt::format("bad expansion pattern: {}", pattern), {
				{"function", "wordexp()"},
				{"pattern",  pattern},
				{"path",     directory}
			});

		case WRDE_NOSPACE:
			throw bad_alloc();

		default:
			throw DetailedError("unknown error", {
				{"function", "wordexp()"},
				{"pattern",  pattern},
				{"path",     directory}
			});
	}

	// Fill vector.
	if (strcmp(exp.we_wordv[0], pattern.c_str()) != 0) {
		for (size_t i = 0; i < exp.we_wordc; i++) {
			results.push_back(string(exp.we_wordv[i]));
		}
	}

	// Cleanup.
	wordfree(&exp);
}

// ---------------------------------------------------------------------------------------------------------------------
// Expansion: glob(3)

vector<string> PathUtil::expand(const string& pattern) {
	return PathUtil::expand(pattern, PathUtil::workdir(), 0);
}

void PathUtil::expand(const string& pattern, vector<string>& results) {
	PathUtil::expand(pattern, PathUtil::workdir(), 0, results);
}

vector<string> PathUtil::expand(const string& pattern, const string& directory) {
	return PathUtil::expand(pattern, directory, 0);
}

void PathUtil::expand(const string& pattern, const string& directory, vector<string>& results) {
	PathUtil::expand(pattern, directory, 0, results);
}

vector<string> PathUtil::expand(const string& pattern, const string& directory, int glob_flags) {
	vector<string> results;
	PathUtil::expand(pattern, directory, glob_flags, results);
	return results;
}

void PathUtil::expand(const string& pattern, const string& directory, int glob_flags, vector<string>& results) {
	string cwd = PathUtil::workdir();
	glob_t exp;

	// Change directory and run wordexp.
	PathUtil::chdir(directory);
	int status = glob(pattern.c_str(), GLOB_ERR | glob_flags, NULL, &exp);
	PathUtil::chdir(cwd);

	// Handle status.
	switch (status) {
		case 0:
			break;

		case GLOB_NOMATCH:
			goto finish;

		case GLOB_ABORTED:
			throw DetailedError(fmt::format("could not read: {}", pattern), {
				{"function", "glob()"},
				{"pattern",  pattern},
				{"path",     directory}
			});

		case GLOB_NOSPACE:
			throw bad_alloc();

		default:
			throw DetailedError("unknown error", {
				{"function", "glob()"},
				{"pattern",  pattern},
				{"path",     directory}
			});
	}

	// Fill vector.
	for (size_t i = 0; i < exp.gl_pathc; i++) {
		results.push_back(string(exp.gl_pathv[i]));
	}

	// Cleanup and return.
	finish:

		globfree(&exp);
}
