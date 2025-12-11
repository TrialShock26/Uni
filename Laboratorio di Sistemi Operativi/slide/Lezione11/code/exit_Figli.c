#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Il padre crea due figli, li aspetta e ne stampa le diverse modalità di uscita */
int main(void) {
    pid_t pid1, pid2;
    int status;

    pid1 = fork();
    if (pid1 < 0) { perror("fork"); exit(1); }
    if (pid1 == 0) {
        printf("FIGLIO 1: termino normalmente.\n");
        exit(0);
    }

    pid2 = fork();
    if (pid2 < 0) { perror("fork"); exit(1); }
    if (pid2 == 0) {
        printf("FIGLIO 2: causo un abort!\n");
        abort();
    }

    // PADRE
    for (int i = 0; i < 2; i++) {
        pid_t pid = wait(&status);
        if (pid == -1) { perror("wait"); exit(1); }

        if (WIFEXITED(status))
            printf("PADRE: figlio %d terminato con codice %d\n",
                   pid, WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("PADRE: figlio %d terminato per segnale %d\n",
                   pid, WTERMSIG(status));
        else
            printf("PADRE: figlio %d terminato in modo sconosciuto\n", pid);
    }

    printf("PADRE: entrambi i figli terminati.\n");
    return 0;
}