/* pipe1: invio di dati da un genitore a un figlio */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLINE 64

int main(void)
{
    int n, fd[2];
    pid_t pid;
    char line[MAXLINE];

    if (pipe(fd) < 0) {
        perror("pipe");
        exit(1);
    }

    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }
    else if (pid > 0) { /* genitore */
        close(fd[0]);                /* chiude estremità di lettura */
        write(fd[1], "hello world\n", 12);
        close(fd[1]);                /* chiude anche l’estremità di scrittura */
    }
    else { /* figlio */
        close(fd[1]);                /* chiude estremità di scrittura */
        n = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO, line, n);
        close(fd[0]);
    }

    exit(0);
}

