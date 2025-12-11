#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_PATH "myfifo"
#define BUF_SIZE 256

int main(void) {
    int fd_fifo;
    char buf[BUF_SIZE];
    ssize_t n;

    /* Crea la FIFO se non esiste */
    if (mkfifo(FIFO_PATH, 0666) < 0) {
        perror("mkfifo");
        // può già esistere, ignoriamo
    }

    /* Apre la FIFO in lettura */
    fd_fifo = open(FIFO_PATH, O_RDONLY);
    if (fd_fifo < 0) {
        perror("open fifo");
        exit(1);
    }

    /* Legge e stampa fino a EOF */
    while ((n = read(fd_fifo, buf, sizeof(buf))) > 0) {
        write(STDOUT_FILENO, buf, n);
    }

    close(fd_fifo);
    unlink(FIFO_PATH);   // rimuove la FIFO dalla directory di lavoro
    return 0;
}

