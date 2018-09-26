#!/usr/bin/env bash
# Package all the Unraid plugins.
# Copyright (C) 2018 Ethan P. (eth-p)

md5sum=''
[ -z "$md5sum" ] && md5sum="$(command -v md5sum)"
[ -z "$md5sum" ] && md5sum="$(command -v md5)"

package_plugin() {
	({
		cd "$1"

		# Find plugin name.
		plugin=$(basename "$(echo *.plg)" ".plg")

		# Create package.
		echo "Creating package: $plugin.txz"
		cd source
		rm "../release/$plugin.txz"
		tar -cJf "../release/$plugin.txz" *
		cd ../

		# Update plugin MD5.
		md5="$("$md5sum" "release/$plugin.txz" | tr ' ' '\n' | tail -n1)"
		echo "Created package. MD5: $md5"

		sed -e 's/\(MD5 \{1,\}\)"[a-z0-9]\{32\}"/\1'"\"$md5\"/" < "$plugin.plg" > "$plugin.plg.tmp" && mv "$plugin.plg.tmp" "$plugin.plg"
	})
}

# Automatic detection:
if [ $# -eq 0 ]; then
	for plugin in */*.plg; do
		if [ -n "$(git status --porcelain "$(dirname "$plugin")")" ]; then
			package_plugin "$(dirname "$plugin")"
		fi
	done
fi

# Manual:
for plugin in "$@"; do
	if ! [ -e "$plugin"/*.plg ]; then
		echo "Unknown plugin: $arg"
		continue
	fi

	package_plugin "$plugin"
done

