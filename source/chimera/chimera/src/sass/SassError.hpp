// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/sass/SassImportEntry.hpp
//       A class which wraps the sass import entry object.
// ---------------------------------------------------------------------------------------------------------------------
#pragma once

#include <iostream>
#include <optional>
#include <string>

#include <sass.h>
// ---------------------------------------------------------------------------------------------------------------------
namespace chimera::sass {
	class SassImportEntry {
		protected:

			const std::string& file;
			std::optional<std::string&> contents;

		public:

			// ----- Constructors / Destructors -----

			/**
			 * Creates an import entry from a file path.
			 * This will leave libsass to handle loading the file from its path.
			 *
			 * @param file The path to the imported file.
			 */
			SassImportEntry(const std::string& file);

			/**
			 * Creates an import entry from an arbitrary file path and a string.
			 *
			 * @param file The "path" to the imported file. This can be anything.
			 * @param contents The contents of the imported file.
			 */
			SassImportEntry(const std::string& file, const std::string& contents);

			/**
			 * Creates an import entry from an arbitrary file path and an input stream.
			 * The input stream will immediate be consumed.
			 *
			 * @param file The "path" to the imported file. This can be anything.
			 * @param contents A input stream for the contents of the imported file.
			 */
			SassImportEntry(const std::string& file, std::istream contents);


			// ----- Getters -----

			/**
			 * Gets the path of the imported file.
			 * @return The path of the imported file.
			 */
			const std::string& getFile() const;

			/**
			 * Gets the contents of the imported file.
			 * @return The file contents, or nothing if the file is to be loaded by liblass.
			 */
			const std::optional<const std::string&> getContents() const;


			// ----- API -----

			/**
			 * Creates a new libsass Sass_Import_Entry object from this.
			 * This object's lifetime must either be managed manually, or have its ownership given to libsass.
			 */
			Sass_Importer_Entry newSass();

	};
}
