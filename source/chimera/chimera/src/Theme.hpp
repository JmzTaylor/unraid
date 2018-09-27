// ---------------------------------------------------------------------------------------------------------------------
// https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
// Unraid's most powerful hybrid theme manager.
//
// Tool: chimera
// File: src/Theme.hpp
//       A chimera theme.
// ---------------------------------------------------------------------------------------------------------------------
#pragma once

#include <map>
#include <string>

#include "ThemeOption.hpp"


namespace chimera {
	class Theme {
		protected:

			std::string file;
			std::map<std::string, ThemeOption> options;
			bool supported;

		public:

			void addOption(ThemeOption);
			ThemeOption removeOption(const std::string& name);
			ThemeOption& getOption(const std::string& name) const;
			void setSupported(bool supported);
			bool isSupported();



	}
}
