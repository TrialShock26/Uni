include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;
    int status;

    printf("[PADRE] PID = %d\n", getpid());

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Processo figlio
        printf("[FIGLIO] Eseguo 'ls -l' con execlp()\n");
        execlp("ls", "ls", "-l", NULL);

        // Se execlp fallisce
        perror("execlp");
        exit(1);
    } else {
        // Processo padre
        wait(&status);
        printf("[PADRE] Il figlio è terminato con codice %d\n", WEXITSTATUS(status));
    }

    return 0;
}
