#!/usr/bin/env bash
# ----------------------------------------------------------------------------------------------------------------------
# https://github.com/eth-p/unraid/tree/master/source/chimera | Copyright (C) 2018 Ethan P. (eth-p)
# Unraid's most powerful hybrid theme manager.
#
# File: chimera/build.sh
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
HEADER_PATHS=()
LIBRARY_PATHS=()
LIBRARY_NAMES=()

# ----------------------------------------------------------------------------------------------------------------------
# Copy Files:

log bld "Copying files..."
run cp -rv "${PLUGIN_HOME}"/plugin/* "${PACKAGE_PLUGIN}/"

# ----------------------------------------------------------------------------------------------------------------------
# Build: chimera tool (libs)

for lib in "${CHIMERA_TOOL}/lib"/*; do
	[ -d "$lib" ] || continue;

	libdir="$lib"
	lib="$(basename "$lib")"

	# Patch library.
	shopt -s nullglob
	patches=("${libdir}/patch"/*)
	if [ "${#patches[@]}" -gt 0 ]; then
		log bld "Patching library '%s'..." "$lib"
		for patch in "${patches[@]}"; do
			apply_patch "${libdir}/repo" "$patch"
		done
	fi

	# Build library.
	wd="$(pwd)"
	log bld "Building library '%s'..." "$lib"
	{
		cd "${libdir}"
		source "build.sh" "${@:2}"
		cd "$wd"
	}
done

# ----------------------------------------------------------------------------------------------------------------------
# Build: chimera tool

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
		LIB_FILES="${LIBRARY_NAMES[*]}" \
		LIB_PATHS="${LIBRARY_PATHS[*]}" \
		LIB_HEADERS="${HEADER_PATHS[*]}" \
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
