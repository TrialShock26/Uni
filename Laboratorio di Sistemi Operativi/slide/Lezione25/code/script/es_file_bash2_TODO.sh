#!/bin/bash

# Controllo argomenti
if [ $# -ne 2 ]; then
    echo "Uso: $0 <utente> <soglia_LWP>"
    exit 1
fi

USER_NAME="$1"
THRESHOLD="$2"

# ps -L -u USER mostra i thread dei processi di USER
# --no-headers evita la riga di intestazione
ps -L -u "$USER_NAME" -o pid,lwp --no-headers | awk -v soglia="$THRESHOLD" '
BEGIN {
    # count[pid] = numero di LWP per quel processo
    proc_over = 0;
}

{
    pid = $1;
    # TODO: incrementare il numero di LWP per questo pid
}

END {
    printf("Processi dell utente %s con più di %d LWP:\n\n", "'"$USER_NAME"'", soglia);

    # TODO: scorrere tutti i pid nell array count
    # e stampare solo quelli con count[pid] > soglia
    # per ogni processo sopra soglia, incrementare proc_over

    # TODO: alla fine stampare il totale
}
'
