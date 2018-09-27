#!/usr/bin/env bash
# ----------------------------------------------------------------------------------------------------------------------
# https://github.com/eth-p/unraid/tree/master/source/custom-css | Copyright (C) 2018 Ethan P. (eth-p)
# A plugin for easily adding persistent custom styles to Unraid.
#
# File: build.sh
#       Build script for the custom-css plugin.
# ----------------------------------------------------------------------------------------------------------------------
if [ -z "${BASH_SOURCE[1]}" ]; then
	printf "error: please use \x1B[33m%s\x1B[0m%s\n" \
		"$(python -c 'import os, sys; print(os.path.relpath(*sys.argv[1:]))' \
		"$(git rev-parse --show-toplevel)/package.sh" "$(pwd)")"
	exit 1
fi

# ----------------------------------------------------------------------------------------------------------------------
# Copy Files:

log bld "Copying files..."
run cp -rv "${PLUGIN_HOME}"/plugin/* "${PACKAGE_PLUGIN}/"

# ----------------------------------------------------------------------------------------------------------------------
# Release:
create_plugin_package
release_plugin_package
