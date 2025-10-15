#!/bin/bash
if [ -z $1 ]
then
	echo "Errore"
	exit 1
fi
echo "Hello World"
ls
echo "argomenti: $1 $2 $# $0"
