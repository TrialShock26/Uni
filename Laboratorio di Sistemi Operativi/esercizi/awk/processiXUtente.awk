{
	utenti[$1]++
}

END {
	for (u in utenti) {
		print u, utenti[u]
	}
}
