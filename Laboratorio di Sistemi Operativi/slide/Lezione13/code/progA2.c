#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void) {
    pid_t pid;
    int status;

    printf("[PADRE] Sono il programma 1 con PID %d\n", getpid());

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // processo figlio
        printf("[FIGLIO] Sto per eseguire prog2 con PID %d\n", getpid());
        execl("./progB", "progB", NULL);

        // se exec fallisce
        perror("execl");
        exit(1);
    } else {
        // processo padre
        printf("[PADRE] Ho creato un figlio con PID %d\n", pid);
        wait(&status);
        printf("[PADRE] Il figlio è terminato con status %d\n", WEXITSTATUS(status));
    }

    return 0;
}
