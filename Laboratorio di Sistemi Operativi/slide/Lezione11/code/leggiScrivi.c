#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Padre crea il figlio che scrive su file, poi legge */

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <nome_file>\n", argv[0]);
        exit(1);
    }

    int fd;
    pid_t pid;
    char buffer[100];

    // Il padre crea (o azzera) il file
    fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, 0666);
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
        char msg[] = "Ciao, sono il figlio!\n";

        // Scrive nel file
        if (write(fd, msg, sizeof(msg) - 1) < 0) {
            perror("write");
            exit(1);
        }

        printf("FIGLIO: ho scritto nel file.\n");
        close(fd);
        exit(0);
    } else {
        // ----- PADRE -----
        // Aspetta che il figlio finisca
        wait(NULL);

        // Riporta il cursore all'inizio
        lseek(fd, 0, SEEK_SET);

        // Legge dal file
        int n = read(fd, buffer, sizeof(buffer) - 1);
        if (n < 0) {
            perror("read");
            exit(1);
        }
        buffer[n] = '\0';

        printf("PADRE: ho letto dal file -> %s", buffer);

        close(fd);
    }

    return 0;
}
