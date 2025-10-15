#!/bin/bash

if [ $# -eq 2 ]; then
	if [ -f $1 ] && [ -e $2 ]; then
		mv $1 temp
		mv $2 $1
		mv temp $2
		echo 'Tutto ok!';
	else
		echo 'Uno dei due argomenti non era un file o directory';
	fi
else
	echo 'Devi fornire esattamente due argomenti';
fi
