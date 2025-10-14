BEGIN {
	print "<html><body>"
	print "<ul>"
}

{
	print "<li>" $0 "</li>"
}

END {
	print "</ul>"
	print "</body></html>"
}
