#!/usr/bin/env bash
# ----------------------------------------------------------------------------------------------------------------------
# https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
# Unraid's most powerful hybrid theme manager.
#
# File: build.sh
#       Build script for the chimera theme manager plugin.
# ----------------------------------------------------------------------------------------------------------------------
if [ -z "${BASH_SOURCE[1]}" ]; then
	printf "error: please use \x1B[33m%s\x1B[0m%s\n" \
		"$(python -c 'import os, sys; print(os.path.relpath(*sys.argv[1:]))' \
		"$(git rev-parse --show-toplevel)/package.sh" "$(pwd)")"
	exit 1
fi

# ----------------------------------------------------------------------------------------------------------------------
# Variables:
CHIMERA_TOOL="${PLUGIN_HOME}/chimera"

# ----------------------------------------------------------------------------------------------------------------------
# Copy Files:

log bld "Copying files..."
run cp -rv "${PLUGIN_HOME}"/plugin/* "${PACKAGE_PLUGIN}/"

# ----------------------------------------------------------------------------------------------------------------------
# Compile Library: libsass

log bld "Building library 'libsass'..."

({
	cd "${CHIMERA_TOOL}/lib/libsass/"
	export BUILD=static
	run make -j4
})

# ----------------------------------------------------------------------------------------------------------------------
# Compile Library: libsemver

log bld "Building library 'libsemver'..."

({
	cd "${CHIMERA_TOOL}/lib/libsemver/"

	# Patch the CMakeLists.txt
	run git checkout head -- CMakeLists.txt
	run git apply "${CHIMERA_TOOL}/lib-patch/libsemver"/*.patch

	[ -f 'Makefile' ]        || run cmake .
	[ -f 'src/libsemver.a' ] || run make -j4
})

# ----------------------------------------------------------------------------------------------------------------------
# Compile Library: fmt

log bld "Building library 'fmt'..."

({
	cd "${CHIMERA_TOOL}/lib/fmt/"
	export BUILD=static
	[ -f 'Makefile' ] || run cmake .
	[ -f 'libfmt.a' ] || run make
})

# ----------------------------------------------------------------------------------------------------------------------
# Patch Library: cxxopts

log bld "Patching library 'cxxopts'..."

({
	cd "${CHIMERA_TOOL}/lib/cxxopts/"

	# Patch.
	run git checkout head -- "$(patch_list_files "${CHIMERA_TOOL}/lib-patch/cxxopts"/*.patch)"
	run git apply "${CHIMERA_TOOL}/lib-patch/cxxopts"/*.patch
})

# ----------------------------------------------------------------------------------------------------------------------
# Compile Binary: chimera

log bld "Building binary 'chimera'..."

({
	cd "${CHIMERA_TOOL}"

	opts=()

	# Clang-specific arguments.
	if g++ 2>&1 | grep clang &>/dev/null; then
		if "$COLOR"; then
			opts+=(-Xclang -fcolor-diagnostics)
		fi
	fi

	run make \
		CXXFLAGS_EXTERNAL="${opts[*]}" \
		BIN_DIR="${BUILD_ROOT}/bin" \
		OBJ_DIR="${BUILD_ROOT}/obj" \
		MACRO_APP_VERSION="${PLUGIN_VERSION}" \
		MACRO_URL_GITHUB="https://github.com/eth-p/unraid/tree/master/source/chimera" \
		MACRO_URL_GITLAB="https://gitlab.com/eth-p/unraid/tree/master/source/chimera" \
		MACRO_URL_LICENSES="https://github.com/eth-p/unraid/tree/master/source/chimera/lib/LICENSES.md"
})

# ----------------------------------------------------------------------------------------------------------------------
# Release:
#create_plugin_package
#release_plugin_package
