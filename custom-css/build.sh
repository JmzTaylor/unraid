#!/usr/bin/env bash
# ----------------------------------------------------------------------------------------------------------------------
# https://github.com/eth-p/unraid/tree/master/custom-css | Copyright (C) 2018 Ethan P. (eth-p)
# A plugin for easily adding persistent custom styles to Unraid.
#
# File: custom-css/build.sh
#       Build script for the custom-css plugin.
# ----------------------------------------------------------------------------------------------------------------------
if [ -z "${BASH_SOURCE[1]}" ]; then
	printf "error: please use \x1B[33m%s\x1B[0m%s\n" \
		"$(python -c 'import os, sys; print(os.path.relpath(*sys.argv[1:]))' \
		"$(git rev-parse --show-toplevel)/package.sh" "$(pwd)")"
	exit 1
fi


# ----------------------------------------------------------------------------------------------------------------------
# Clear Files:
log inf "Removing files..."
run rm -rv "$PLUGIN_TARGET"/*

# ----------------------------------------------------------------------------------------------------------------------
# Copy Files:

log inf "Copying files..."
run cp -rv "${PLUGIN_DIR}/res"/* "${PLUGIN_TARGET}/"

# ----------------------------------------------------------------------------------------------------------------------
# Package Files:
create_plugin_package
