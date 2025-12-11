#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];
    char buf[64];
    pid_t pid;

    pipe(fd);

    if ((pid = fork()) == 0) {   // Figlio lettore
        // ERRORE: non chiude fd[1] (scrittura)
        // close(fd[1]);   // <- manca di proposito
        while (read(fd[0], buf, sizeof(buf)) > 0)
            write(STDOUT_FILENO, buf, 5);
        close(fd[0]);
        _exit(0);
    } else {                     // Padre scrittore
        close(fd[0]);            // chiude lettura
        write(fd[1], "ciao\n", 5);
        close(fd[1]);            // segnala EOF (ma il figlio tiene ancora aperto fd[1])
        printf("Padre: attendo il figlio...\n");
        wait(NULL);              // <-- si blocca per sempre!
        printf("Padre: figlio terminato.\n");
    }
}
