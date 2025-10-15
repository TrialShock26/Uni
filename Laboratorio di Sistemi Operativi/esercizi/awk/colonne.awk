NR == 1 {chiave=substr($1, 1, 1);next}
match($2, "^"chiave".*"chiave"$") {print $3}
