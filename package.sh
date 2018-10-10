#!/usr/bin/env bash
# ----------------------------------------------------------------------------------------------------------------------
# https://github.com/eth-p/unraid | Copyright (C) 2018 Ethan P. (eth-p)
# A collection of eth-p's Unraid plugins.
#
# File: package.sh
#       A script to build/package Unraid plugins.
#
# Usage:
#       ./package.sh                 -- Builds all modified plugins.
#       ./package.sh [plugin]        -- Builds a specific plugin.
# ----------------------------------------------------------------------------------------------------------------------
# Polyfill: md5sum

[ -z "$(type -t md5sum)" ] && command -v md5 &>/dev/null && md5sum() {
	local line
	while read -r line; do
		local file="$(sed -e 's/^MD5 (\([^)]*\).*$/\1/' <<< "$line")"
		local hash="$(tr ' ' '\n' <<< "$line" | tail -n1)"
		printf "%s  %s" "$hash" "$file"
	done < <(command md5 "$@")
}

# ----------------------------------------------------------------------------------------------------------------------
# Polyfill: realpath

[ -z "$(type -t realpath)" ] && realpath() {
	if [ "$1" = "--" ]; then shift; fi
	python -c "import os,sys; print os.path.realpath(sys.argv[1])" "$1"
}

# ----------------------------------------------------------------------------------------------------------------------
# Variables

COLOR="$(grep -e "color" -e "256" <<< "$TERM" &>/dev/null && echo "true" || echo "false")"

# ----------------------------------------------------------------------------------------------------------------------
# Function: log

# Logs a message.
# $1: ["inf"|"wrn"|"err"] The message level.
# $2: [String] The format string.
# ... [String] The format arguments.
if "$COLOR"; then
	log() {
		local level="$1"
		local format="${LOG_PREFIX}$2"
		local args=("${@:3}")
		local color=""

		case "$level" in
			"inf") color='';;
			"wrn") color='\x1B[33m';;
			"err") color='\x1B[31m';;
			"ist") color='\x1B[35m';;
			"bld") color='\x1B[36m';;
			"fin") color='\x1B[32m';;
		esac

		printf "\x1B[2m%s\x1B[0m ${color}[%s]\x1B[0m ${format}\n" "$(date +"%H:%M:%S")" "$level" "${args[@]}"
	}
else
	log() {
		local level="$1"
		local format="${LOG_PREFIX}$2"
		local args=("${@:2}")

		printf "%s %s: ${format}\n" "$(date +"%H:%M:%S")" "${args[@]}"
	}
fi

# ----------------------------------------------------------------------------------------------------------------------
# Function: run

# Runs a command.
# $1: [String] The command.
# ... [String] The command arguments.
run() {
	local command="$1"
	local args=("${@:2}")

	run_display_args "$@"

	"$command" "${args[@]}" 2> >(run_display_err) 1> >(run_display_out)
	local result=$?

	if [ $result -ne 0 ]; then
		exit $result
	fi

	return $result
}

# Runs a command, not caring if it fails.
# $1: [String] The command.
# ... [String] The command arguments.
run_c() {
	local command="$1"
	local args=("${@:2}")

	run_display_args "$@"

	"$command" "${args[@]}" 2> >(run_display_err) 1> >(run_display_out)
	return $?
}

if "$COLOR"; then
	run_display_args() {
		if $VERBOSE; then
			printf "\x1B[34m\$ %s\x1B[0m" "$1"
			printf " %q" "${@:2}"
			printf "\n"
		fi
	}

	run_display_err() {
		while read -r line; do
			printf "\x1B[31m|\x1B[0m %s\n" "$line"
		done
	}

	run_display_out() {
		if $VERBOSE_EXTRA; then
			while read -r line; do
				printf "\x1B[33m|\x1B[0m %s\n" "$line"
			done
		else
			cat - >/dev/null
		fi
	}
else
	run_display_args() {
		if $VERBOSE; then
			echo "$@"
		fi
	}

	run_display_err() {
		while read -r line; do
			printf "! %s\n" "$line"
		done
	}

	run_display_out() {
		if $VERBOSE_EXTRA; then
			while read -r line; do
				$VERBOSE && printf "| %s\n" "$line"
			done
		fi
	}
fi

# ----------------------------------------------------------------------------------------------------------------------
# Function: apply_patch

# Applies a patch using git.
# $1: [File] The repo directory path.
# $2: [File] The patch file.
apply_patch() {
	local repo="$1"
	local patches="${@:2}"
	({
		cd "$repo"
		files=()
		while read -r file; do
			files+=("$file")
		done < <(cat "${patches[@]}" | grep '^+++ ' | sed 's/+++ [^/]*\///')

		run git checkout head -- "${files[@]}"
		run git apply "${patches[@]}"
	})
}

# ----------------------------------------------------------------------------------------------------------------------
# Function: create_plugin_package

# Creates a plugin package.
# This uses the PLUGIN* and BUILD* variables for arguments.
create_plugin_package() {
	({
		log bld "Creating package..."
		local md5=''
		local out_package="${BUILD_ROOT}/out/${PLUGIN_NAME}.txz"
		local out_plgfile="${BUILD_ROOT}/out/${PLUGIN_NAME}.plg"

		# Create xz tarball.
		(cd "${BUILD_ROOT}/in" && run tar --exclude='.*' -vcJf "$out_package" *)

		# Update plugin MD5.
		md5="$(md5sum "$out_package" | cut -d' ' -f1)"
		sed -e 's/\(MD5 \{1,\}\)"[^"]\{1,\}"/\1'"\"$md5\"/" < "$PLUGIN_FILE" > "$out_plgfile"

		log inf "Created package with hash: %s" "$md5"
	})
}

# ----------------------------------------------------------------------------------------------------------------------
# Function: release_plugin_package

# Releases a plugin package.
# This uses the PLUGIN* and BUILD* variables for arguments.
release_plugin_package() {
	({
		local out_package="${BUILD_ROOT}/out/${PLUGIN_NAME}.txz"
		local out_plgfile="${BUILD_ROOT}/out/${PLUGIN_NAME}.plg"

		run cp -v -- "$out_package" "$RELEASES/$(basename "$out_package")"
		run cp -v -- "$out_plgfile" "$RELEASES/$(basename "$out_plgfile")"

		log fin "Prepared %s (%s)" "${PLUGIN_NAME}" "${PLUGIN_VERSION}"
		log fin "You need to do a git push to release the plugin."
	})
}

# ----------------------------------------------------------------------------------------------------------------------
# Function: patch_list_files

# Lists modified files in one or more patches.
# $1: [String] The patch file.
# ... [String] ...
patch_list_files() {
	cat "$@" | grep "+++\|---" | sed 's/[+\-]\{3\} [a|b]\/\(.*\)$/\1/' | uniq
}

# ----------------------------------------------------------------------------------------------------------------------
# Function: __plugin_build

# Runs a plugin build script.
# $1: [String] The path to the plugin file.
__plugin_build() {
	GLOBIGNORE=".:..:.DS_Store:._*";
	PLUGIN_FILE="$(realpath "$1")"
	PLUGIN_HOME="$(dirname "$PLUGIN_FILE")"
	PLUGIN_NAME="$(grep -e 'name \{1,\}"[0-9a-zA-Z\.\-]\{1,\}"' < "$PLUGIN_FILE" | grep -o '[^"]*">$' | sed -e 's/..$//')"
	PLUGIN_VERSION="$(grep -e 'version \{1,\}"[0-9a-z\.]\{1,\}"' < "$PLUGIN_FILE" | grep -o '[^"]*">$' | sed -e 's/..$//')"
	RELEASES="${SELF}/release"
	BUILD_TARGET="release"
	BUILD_ROOT="${SELF}/target/${PLUGIN_NAME}/${BUILD_TARGET}"
	PACKAGE_ROOT="${BUILD_ROOT}/in"
	PACKAGE_PLUGIN="${BUILD_ROOT}/in/usr/local/emhttp/plugins/${PLUGIN_NAME}"

	# Safety checks.
	if [ -z "$PLUGIN_NAME"  ]; then log err '$PLUGIN_NAME is empty.';    return 1; fi
	if [ -z "$PLUGIN_NAME"  ]; then log err '$PLUGIN_VERSION is empty.'; return 1; fi
	if [ -z "$BUILD_ROOT"   ]; then log err '$BUILD_ROOT is empty.';     return 1; fi
	if [ -z "$PACKAGE_ROOT" ]; then log err '$PACKAGE_ROOT is empty.';   return 1; fi

	# Check for a build script.
	if ! [ -f "${PLUGIN_HOME}/build.sh" ]; then
		log err "%s: no build.sh script!" "${PLUGIN_NAME}"
		return 255
	fi

	# Log the action.
	printf -- '-%.0s' $(seq 1 $(tput cols))
	printf "Building: %s.plg\n" "$PLUGIN_NAME"
	printf "Version:  %s\n\n" "$PLUGIN_VERSION"

	# Create the build directories.
	$CLEAN && rm -rf "$BUILD_ROOT"
	[ -d "$BUILD_ROOT" ]       || mkdir -p "$BUILD_ROOT"
	[ -d "${BUILD_ROOT}/out" ] || mkdir -p "${BUILD_ROOT}/out"
	[ -d "$PACKAGE_PLUGIN" ]   || mkdir -p "$PACKAGE_PLUGIN"
	[ -d "$RELEASES" ]         || mkdir -p "$RELEASES"

	# Run the build script.
	LOG_PREFIX="$(rev <<< "$PLUGIN_NAME" | cut -d'.' -f1 | rev): "
	(shopt -u dotglob; source "${PLUGIN_HOME}/build.sh")
	local result=$?
	LOG_PREFIX=""

	# Handle the result.
	if [ $result -ne 0 ]; then
		$COLOR && printf "\n\x1B[31mBuild Failed.\x1B[0m\n"
		$COLOR || printf "\nBuild Failed.\n"
	fi

	printf -- '-%.0s' $(seq 1 $(tput cols))
	return $result
}

# ----------------------------------------------------------------------------------------------------------------------
# Main: (Arguments)
SELF="$(dirname "$(realpath "${BASH_SOURCE[0]}")")"
VERBOSE=false
VERBOSE_EXTRA=false
CLEAN=false
while true; do
	case "$1" in
		"--")                    shift; break;;
		"-v"|"--verbose")        shift; VERBOSE=true;;
		"-vv"|"--extra-verbose") shift; VERBOSE=true; VERBOSE_EXTRA=true;;
		"-c"|"--clean")          shift; CLEAN=true;;
		"-"*)                    echo "Unknown argument: $1"; exit 255;;
		""|*)                    break;;
	esac
done

# ----------------------------------------------------------------------------------------------------------------------
# Main: (Changed Plugins)
if [ $# -eq 0 ]; then
	for plugin in "$(dirname "${BASH_SOURCE[0]}")"/source/*/manifest.plg; do
		if [ -n "$(git status --porcelain "$(dirname "$plugin")")" ]; then
			__plugin_build "$plugin"
		fi
	done
fi

# ----------------------------------------------------------------------------------------------------------------------
# Main: (Manual)
plugins=("$@")

if [ "${plugins[0]}" = "*" ]; then
	plugins=("$(dirname "${BASH_SOURCE[0]}")/source"/*)

	for index in $(seq 0 $((${#plugins[@]} - 1))); do
		plugins[index]="$(basename "${plugins[index]}")"
	done
fi

for plugin in "${plugins[@]}"; do
	if ! [ -e "$(dirname "${BASH_SOURCE[0]}")/source/${plugin}"/manifest.plg ]; then
		log err "package.sh: unknown plugin '%s'" "$plugin"
		continue
	fi

	__plugin_build "$(dirname "${BASH_SOURCE[0]}")/source/${plugin}/manifest.plg"
	result=$?
	if [ $result -ne 0 ]; then
		exit $result
	fi
done
