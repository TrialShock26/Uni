include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_CMD 128

int main(void) {
    char comando[MAX_CMD];
    ssize_t nread;
    pid_t pid;
    int status;

    printf("Inserisci un comando da eseguire (es. ls, date, who): ");
    fflush(stdout);  // importante, perché printf è bufferizzato

    // Legge da stdin (file descriptor 0)
    nread = read(STDIN_FILENO, comando, sizeof(comando) - 1);
    if (nread < 0) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // Termina la stringa letta
    comando[nread] = '\0';

    // Rimuove eventuale '\n' finale
    comando[strcspn(comando, "\n")] = '\0';

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

if (pid == 0) {
        // Processo figlio
        printf("[FIGLIO] Eseguo '%s' tramite execlp()\n", comando);
        execlp(comando, comando, (char *)NULL);

        // Se execlp fallisce
        perror("execlp");
        _exit(127);
    }

    // Processo padre
    if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }

    if (WIFEXITED(status)) {
        printf("[PADRE] Figlio terminato con codice %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("[PADRE] Figlio terminato da segnale %d\n", WTERMSIG(status));
    }

    return 0;
}
