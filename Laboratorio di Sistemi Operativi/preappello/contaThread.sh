#!/bin/bash

user="$1"
soglia="$2"

ps -L -u "$user" -o pid,lwp --no-headers | awk -v soglia="$soglia" '
BEGIN {
}

{
	pid = $1;
}
