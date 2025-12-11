#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void on_sig(int s) {
    if (s == SIGINT)   printf("[aspetta] Ricevuto SIGINT\n");
    if (s == SIGUSR1)  printf("[aspetta] Ricevuto SIGUSR1\n");
    // torna al punto interrotto
}

int main(void) {
    if (signal(SIGINT,  on_sig) == SIG_ERR) { perror("signal"); exit(1); }
    if (signal(SIGUSR1, on_sig) == SIG_ERR) { perror("signal"); exit(1); }

    printf("PID=%d — invia SIGINT o SIGUSR1 con 'kill -SIGINT %d' / 'kill -SIGUSR1 %d'\n",
           getpid(), getpid(), getpid());

    for (;;) pause();   // attende segnali indefinitamente
}
