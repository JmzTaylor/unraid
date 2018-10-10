#!/usr/bin/env bash
# ----------------------------------------------------------------------------------------------------------------------
# https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
# Unraid's most powerful hybrid theme manager.
#
# File: chimera/build/semver/build.sh
# ----------------------------------------------------------------------------------------------------------------------
({
	cd repo
	export BUILD=static
	[ -f 'Makefile' ]        || run cmake .
	[ -f 'src/libsemver.a' ] || run make -j4
})

HEADER_PATHS+=("lib/${lib}/repo/include")
LIBRARY_PATHS+=("lib/${lib}/repo/src")
LIBRARY_NAMES+=("semver")
