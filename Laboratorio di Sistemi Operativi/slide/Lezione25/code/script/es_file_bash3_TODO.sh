#!/bin/bash

# TODO: controllare che sia stato passato un argomento
FILE="$1"

# TODO: controllare che il file esista

# Ricavare solo il nome del file (senza percorso)
BASENAME=$(basename "$FILE")

# TODO: estrarre la prima lettera di BASENAME (usare cut)
# FIRST=$( ... )

# TODO: estrarre l'ultima lettera di BASENAME (usare cut)
# LAST=$( ... )

# TODO:
# tutte le parole che iniziano con FIRST e finiscono con LAST
# con il nome del file BASENAME.
#
# Suggerimento: usare i delimitatori di parola POSIX \< e \>
#