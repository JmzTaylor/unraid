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
	python -c "import os,sys; print os.path.realpath(sys.argv[1])" "$1"
}

# ----------------------------------------------------------------------------------------------------------------------
# Function: log

# Logs a message.
# $1: ["inf"|"wrn"|"err"] The message level.
# $2: [String] The format string.
# ... [String] The format arguments.
if grep -e "color" -e "256" <<< "$TERM" &>/dev/null; then
	log() {
		local level="$1"
		local format="${LOG_PREFIX}$2"
		local args=("${@:3}")
		local color=""

		case "$level" in
			"inf") color='';;
			"wrn") color='\x1B[33m';;
			"err") color='\x1B[31m';;
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
if grep -e "color" -e "256" <<< "$TERM" &>/dev/null; then
	run() {
		local command="$1"
		local args=("${@:2}")

		if $VERBOSE; then
			printf "\x1B[34m\$ %s\x1B[0m" "$command"
			printf " %q" "${args[@]}"
			printf "\n"
		fi

		"$command" "${args[@]}" | run_display
	}

	run_display() {
		if $VERBOSE_EXTRA; then
			while read -r line; do
				$VERBOSE && printf "\x1B[33m|\x1B[0m %s\n" "$line"
			done
		fi
	}
else
	run() {
		local command="$1"
		local args=("${@:2}")

		if $VERBOSE; then
			printf "$ %s" "$command"
			printf " %q" "${args[@]}"
			printf "\n"
		fi

		"$command" "${args[@]}" | run_display
	}

	run_display() {
		if $VERBOSE_EXTRA; then
			while read -r line; do
				$VERBOSE && printf "\x1B[33m|\x1B[0m %s\n" "$line"
			done
		fi
	}
fi


# ----------------------------------------------------------------------------------------------------------------------
# Function: create_plugin_package

# Creates a plugin package.
# This uses the PLUGIN* variables for arguments.
create_plugin_package() {
	({
		log inf "Creating package..."
		local md5=''
		local package="${PLUGIN_RELEASES}/${PLUGIN_NAME}.txz"

		# Create xz tarball.
		(cd "$PLUGIN_TARGET" && run tar -vcJf "$package" *) 2> >(run_display)

		# Update plugin MD5.
		md5="$(md5sum "$package" | cut -d' ' -f1)"
		sed -e 's/\(MD5 \{1,\}\)"[a-z0-9]\{32\}"/\1'"\"$md5\"/" < "$PLUGIN_FILE" > "${PLUGIN_FILE}.tmp" && mv "${PLUGIN_FILE}.tmp" "${PLUGIN_FILE}"

		log inf "Created package with hash: %s" "$md5"
	})
}

# ----------------------------------------------------------------------------------------------------------------------
# Function: __plugin_build

# Runs a plugin build script.
# $1: [String] The path to the plugin file.
__plugin_build() {
	GLOBIGNORE=".:..:.DS_Store:._*";
	PLUGIN_FILE="$(realpath "$1")"
	PLUGIN_DIR="$(dirname "$PLUGIN_FILE")"
	PLUGIN_NAME="$(basename "$PLUGIN_FILE" .plg)"
	PLUGIN_TARGET="${PLUGIN_DIR}/.target/release"
	PLUGIN_VERSION="$(grep -e 'version \{1,\}"[0-9a-z\.]\{1,\}"' < "$PLUGIN_FILE" | grep -o '[^"]*">$' | sed -e 's/..$//')"
	PLUGIN_RELEASES="${PLUGIN_DIR}/release"

	# Check for a build script.
	if ! [ -f "${PLUGIN_DIR}/build.sh" ]; then
		log err "%s: no build.sh script!" "${PLUGIN_NAME}"
		return 255
	fi

	# Log the action.
	printf -- '-%.0s' $(seq 1 $(tput cols))
	printf "Building: '%s'.plg\n" "$PLUGIN_NAME"
	printf "Version:  %s\n\n" "$PLUGIN_VERSION"

	# Create the target and release directories.
	[ -d "$PLUGIN_TARGET" ]   || mkdir -p "$PLUGIN_TARGET"
	[ -d "$PLUGIN_RELEASES" ] || mkdir -p "$PLUGIN_RELEASES"

	# Run the build script.
	LOG_PREFIX="$(rev <<< "$PLUGIN_NAME" | cut -d'.' -f1 | rev): "
	(shopt -u dotglob; source "${PLUGIN_DIR}/build.sh")
	LOG_PREFIX=""
}

# ----------------------------------------------------------------------------------------------------------------------
# Main: (Arguments)
VERBOSE=false
VERBOSE_EXTRA=false
while true; do
	case "$1" in
		"--")                    shift; break;;
		"-v"|"--verbose")        shift; VERBOSE=true;;
		"-vv"|"--extra-verbose") shift; VERBOSE=true; VERBOSE_EXTRA=true;;
		"-"*)                    echo "Unknown argument: $1"; exit 255;;
		""|*)                    break;;
	esac
done

# ----------------------------------------------------------------------------------------------------------------------
# Main: (Changed Plugins)
# Automatic detection:
if [ $# -eq 0 ]; then
	for plugin in "$(dirname "${BASH_SOURCE[0]}")"/*/*.plg; do
		if [ -n "$(git status --porcelain "$(dirname "$plugin")")" ]; then
			__plugin_build "$plugin"
		fi
	done
fi

# ----------------------------------------------------------------------------------------------------------------------
# Main: (Manual)
for plugin in "$@"; do
	if ! [ -e "$(dirname "${BASH_SOURCE[0]}")/${plugin}"/*.plg ]; then
		log err "package.sh: unknown plugin '%s'" "$plugin"
		continue
	fi

	__plugin_build "$plugin"/*.plg
done
