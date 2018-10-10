# ----------------------------------------------------------------------------------------------------------------------
# https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
# Unraid's most powerful hybrid theme manager.
#
# File: Makefile
#       Makefile used to build utility programs.
#       DO NOT RUN THIS NORMALLY.
#       USE THE PROVIDED BUILD SCRIPTS!
# ----------------------------------------------------------------------------------------------------------------------
# Options:

COMPILER_O=
COMPILER_STD=-std=c++17
COMPILER_WARN=-Wall -Werror -Wno-unused-command-line-argument -Wfatal-errors
COMPILER_MACROS=

# ----------------------------------------------------------------------------------------------------------------------
# Libraries:

LIB_HEADERS=lib/libsass/include \
            lib/libsemver/include \
            lib/cxxopts/include \
            lib/json/include \
            lib/fmt/include

LIB_PATHS=lib/libsass/lib \
          lib/libsemver/src \
          lib/fmt/

LIB_FILES=sass \
          semver \
          fmt \

# ----------------------------------------------------------------------------------------------------------------------
# Compiler:

CXX=g++
CXXFLAGS=-g $(COMPILER_STD) $(COMPILER_O) $(foreach h,$(LIB_HEADERS),-I $h)
LDFLAGS=$(foreach p,$(LIB_PATHS),-L $p)
LDLIBS=$(foreach l,$(LIB_FILES),-l$l)

# ----------------------------------------------------------------------------------------------------------------------
# Paths:

SRC_DIR=src
BIN_DIR=/dev/null
OBJ_DIR=/dev/null

# ----------------------------------------------------------------------------------------------------------------------
# Files:

NAME=$(notdir $(realpath .))
SOURCES=$(shell find $(SRC_DIR) -name '*.cpp')
MAIN=$(filter %/main.cpp,$(SOURCES))
OBJECTS=$(addprefix $(OBJ_DIR)/,$(patsubst %.cpp,%.o,$(SOURCES)))

# ----------------------------------------------------------------------------------------------------------------------
# Targets:

# Disable built-in rule.
%: %.cpp

# From *.cpp --> *.o
$(OBJ_DIR)/%.o : %.cpp
	@ mkdir -p $(dir $@)
	$(CXX) $(COMPILER_WARN) -c $(CXXFLAGS) $(CXXFLAGS_EXTERNAL) $(LDFLAGS) \
		$(foreach m,$(COMPILER_MACROS),-D$m) \
		$(foreach m,$(filter MACRO_%,$(.VARIABLES)),-D$(patsubst MACRO_%,%,$m)=\"$($(m))\") \
		$< -o $@

# From *.o --> executable
$(BIN_DIR)/$(NAME) : $(OBJECTS)
	@ mkdir -p $(BIN_DIR)
	$(CXX) $(shell lorder $^ | tsort) $(LDFLAGS) $(LDLIBS) -o $@

# Aliases.
$(NAME): $(BIN_DIR)/$(NAME)
all: $(NAME)
