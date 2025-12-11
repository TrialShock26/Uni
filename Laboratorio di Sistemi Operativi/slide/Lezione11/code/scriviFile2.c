#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/* Padre e figlio stampano su file aperto dopo il fork*/

int main(int argc, char * argv[]) {
    int fd;
    pid_t pid;

    pid = fork();

    // padre e figlio aprono o creano il file
    fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd < 0) {
        perror("open");
        exit(1);
    }


    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // ----- FIGLIO -----
        write(fd, "Messaggio del figlio\n", 22);
        printf("FIGLIO: ho scritto nel file.\n");
    } else {
        // ----- PADRE -----
        write(fd, "Messaggio del padre\n", 21);
        printf("PADRE: ho scritto nel file.\n");
    }

    close(fd);
    return 0;
}
