#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define SHM_PATH "shared_mem"
#define MAX_SIZE 8192   // dimensione massima (8 KB per esempio)

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <file>\n", argv[0]);
        exit(1);
    }

    int fd_src = open(argv[1], O_RDONLY);
    if (fd_src < 0) { perror("open file"); exit(1); }

    // crea file condiviso
    int fd_shm = open(SHM_PATH, O_CREAT | O_RDWR, 0666);
    if (fd_shm < 0) { perror("open shared file"); exit(1); }

    // dimensiona il file condiviso
    if (ftruncate(fd_shm, MAX_SIZE) < 0) { perror("ftruncate"); exit(1); }

    // mappa la memoria condivisa
    void *addr = mmap(NULL, MAX_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
    if (addr == MAP_FAILED) { perror("mmap"); exit(1); }

    // copia i dati dal file alla memoria
    ssize_t n;
    size_t offset = 0;
    char buf[256];
    while ((n = read(fd_src, buf, sizeof(buf))) > 0) {
        memcpy((char *)addr + offset, buf, n);
        offset += n;
    }

    // aggiunge terminatore (utile per il reader)
    ((char *)addr)[offset] = '\0';

    printf("Writer: scritto %zu byte in memoria condivisa.\n", offset);

    munmap(addr, MAX_SIZE);
    close(fd_src);
    close(fd_shm);

    return 0;
}
