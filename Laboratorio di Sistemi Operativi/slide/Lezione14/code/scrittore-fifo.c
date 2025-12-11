#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_PATH "myfifo"
#define BUF_SIZE 256

int main(int argc, char *argv[]) {
    int fd_fifo, fd_file;
    char buf[BUF_SIZE];
    ssize_t n;

    if (argc != 2) {
        fprintf(stderr, "Uso: %s <file>\n", argv[0]);
        exit(1);
    }

    /* Crea la FIFO nella directory corrente */
    if (mkfifo(FIFO_PATH, 0666) < 0) {
        perror("mkfifo");
        // se già esiste non è un errore critico
    }

    /* Apre il file da leggere */
    fd_file = open(argv[1], O_RDONLY);
    if (fd_file < 0) {
        perror("open file");
        exit(1);
    }

    /* Apre la FIFO in scrittura (bloccante finché non c'è un lettore) */
    fd_fifo = open(FIFO_PATH, O_WRONLY);
    if (fd_fifo < 0) {
        perror("open fifo");
        exit(1);
    }

    /* Copia dal file alla FIFO */
    while ((n = read(fd_file, buf, sizeof(buf))) > 0) {
        if (write(fd_fifo, buf, n) != n) {
            perror("write fifo");
            break;
        }
    }

    close(fd_file);
    close(fd_fifo);
    return 0;
}
