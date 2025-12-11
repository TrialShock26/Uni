#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {

    printf("[P] start:      PID=%d PPID=%d\n", getpid(), getppid());

    pid_t child = fork();
    if (child < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child == 0) {
        // FIGLIO
        printf("[C] start:      PID=%d PPID=%d\n", getpid(), getppid());

        for (int i = 0; i < 10; i++) {
            sleep(1);
            printf("[C] t=%d  PID=%d PPID=%d\n", i+1, getpid(), getppid());
        }

        return 0;

    } else {
        // PADRE
        printf("[P] child PID=%d, dormo 3 secondi poi esco...\n", child);
        sleep(3);
        printf("[P] exiting now.\n");
        _exit(0);
    }
}
