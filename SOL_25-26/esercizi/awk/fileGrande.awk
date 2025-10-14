NR > 1 && $1 ~ /^-/ {
	if ($5 > max) {
		max=$5
		file=$9
	}
}
END {print file}
