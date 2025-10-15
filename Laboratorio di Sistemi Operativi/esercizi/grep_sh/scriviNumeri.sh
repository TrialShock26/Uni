#!/bin/bash

if [ $# -eq 1 ]; then
	i=0
	while [ $i -lt $1 ]; do
		echo $((i++))
		#i=$((i+1))
	done
else
	echo 'Inserisci solo il valore di N'
fi
