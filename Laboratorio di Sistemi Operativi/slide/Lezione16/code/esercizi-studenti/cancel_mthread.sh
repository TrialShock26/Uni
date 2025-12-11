#!/bin/bash

C_FILE="cancel_mthread.c"
ESEGUIBILE="./mthread"

#Compilazione
if ! gcc -o $ESEGUIBILE $C_FILE -lpthread; then
    exit 1
fi
# Avvia il programma in background e invia INVIO per sbloccarlo grazie ad echo
echo | $ESEGUIBILE &

#Prende il PID
PID=$!
sleep 1

echo "Prima della cancellazione"
if ! ps -Lf -p $PID; then
    exit 1
fi

sleep 4

echo "Dopo la cancellazione"
if ! ps -Lf -p $PID; then
    exit 1
fi
#Aspetta fine del processo
wait $PID
