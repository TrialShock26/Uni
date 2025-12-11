#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define SHM_PATH "shared_mem"
#define MAX_SIZE 8192

int main(void) {
    int fd_shm = open(SHM_PATH, O_RDONLY);
    if (fd_shm < 0) { perror("open shared file"); exit(1); }

    void *addr = mmap(NULL, MAX_SIZE, PROT_READ, MAP_SHARED, fd_shm, 0);
    if (addr == MAP_FAILED) { perror("mmap"); exit(1); }

    // stampa i dati presenti nella memoria condivisa
    printf("%s", (char *)addr);

    munmap(addr, MAX_SIZE);
    close(fd_shm);

    // rimuove il file usato per la memoria condivisa
    unlink(SHM_PATH);
    return 0;
}
