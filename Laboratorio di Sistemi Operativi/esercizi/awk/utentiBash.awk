BEGIN {FS=":"}
$7=="/bin/bash" {print $1}
