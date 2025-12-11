#!/bin/bash

# TODO: controllare che ci siano esattamente 2 argomenti

DIR= %TODO
STR="%TODO

# TODO: controllare che DIR sia una directory valida

old_count=-1   # numero precedente di file che contengono STR

while true; do
    count=0

    # Scorro tutti i file .txt nella directory
    for f in "$DIR"/*.txt; do
        # TODO: verificare che f sia davvero un file regolare

        # TODO: usare grep -q per controllare se il file contiene STR
        # se sì, incrementare count
    done

    # TODO: se count e' diverso da old_count, stampare un messaggio
    #       e aggiornare old_count

    sleep 5
done
