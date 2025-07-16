#!/bin/bash

### Functions ###
re_compile() {
	clear
	make || make re
	[[ $? != 0 ]] && echo error && return 1
	clear
	date
	./$executable $args
}
check_for_updates() {
	oldmod=0
	while true; do
		for file in "${files_to_track[@]}"; do
			newmod=$(stat -c %Y "$file")
			if [[ $newmod > $oldmod ]]; then
				oldmod=$newmod
				re_compile
			fi
		done
		read -t 2 && exit 1
	done
}

### Globals ###
executable="cub3D"
args="maps/normal.cub"
files_to_track=(sources/*.c)

### Program ###
re_compile
check_for_updates
