 #include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    size_t SIZE = 256;
    char *shared = mmap(NULL, SIZE,
                        PROT_READ | PROT_WRITE,
                        MAP_SHARED | MAP_ANONYMOUS,
                        -1, 0);
    if (shared == MAP_FAILED) {
        perror("mmap");
        return 1;
    }
 
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }

    if (pid == 0) {
        // FIGLIO: scrive nel buffer
        strcpy(shared, "Ciao dal figlio via mmap anonima!");
        _exit(0);
    }

    // PADRE: aspetta e poi legge
    waitpid(pid, NULL, 0);
    printf("[Padre] Letto: \"%s\"\n", shared);

    munmap(shared, SIZE);
    return 0;
}