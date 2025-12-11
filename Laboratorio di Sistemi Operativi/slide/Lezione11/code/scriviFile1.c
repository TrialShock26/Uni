#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/* Padre e figlio stampano su file aperto prima del fork*/

int main() {
    int fd;
    pid_t pid;

    // Il padre apre o crea il file
    fd = open("scambio.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    pid = fork();

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
