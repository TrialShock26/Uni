#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int counter = 0;  // contatore globale

void handler(int signo) {
    counter++;
    printf("\n[handler] Ricevuto SIGINT (Ctrl-C) numero %d\n", counter);

    if (counter >= 3) {
        printf("[handler] Ho ricevuto 3 SIGINT, termino il programma.\n");
        exit(0);   // termina il processo
    }
}

int main(void) {
    // Installa il gestore
    if (signal(SIGINT, handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    printf("PID = %d\n", getpid());
    printf("Premi Ctrl-C (3 volte per uscire)\n");

    // Ciclo infinito: il programma attende segnali
    while (1) {
        printf("Lavoro...\n");
        sleep(2);
    }

    return 0;
}
