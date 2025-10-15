#!/bin/bash

for u in $(ps -e -o user= | sort -u); do
	ps -u $u -o pid= > pids-$u.txt
done
