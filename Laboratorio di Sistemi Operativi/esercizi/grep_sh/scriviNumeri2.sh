#!/bin/bash

if [ $# -eq 0 ]; then
	i=20
#	while [ $i -ge 10 ]; do
#		echo $i
#		i=$((i-1))
#	done
	until [ $i -lt 10 ]; do
		echo $i
		i=$((i-1))
	done
else
	echo 'Non servono argomenti';
fi
