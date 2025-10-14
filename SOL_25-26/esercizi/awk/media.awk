function media (somma, n) {
	return somma/n
}

{
	tot += $1
	count++;
}

END {
	print "Media:", media(tot, count)
}
