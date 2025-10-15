#!/bin/bash
if [ $# -ne 1 ]; then
	echo 'Devi specificare solo un percorso'
	exit 1
fi

cd $1
for f in *; do #$(ls $1); do
	if [ -f $f ] && [ -r $f ]; then
		cat $f
	fi
done
