#!/bin/bash

if [ $# -ne 2 ]; then
	echo 'Errore'
	exit 1
fi

DIR=$1
STR=$2
oldCount=-1
while true; do
	count = 0
	for f in "$DIR"/*.txt; do
		if [ -f "$f" ]; then
			if [ grep STR -q f ]; then
				count=$((count+1))
			fi
		fi
	done
	if [ $count -ne $oldCount //TODO
done
