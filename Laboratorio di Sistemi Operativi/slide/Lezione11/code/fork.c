#include <stdio.h>
#include <unistd.h>

/* Primo esempio di fork */
int main() {
    int x = 1;

    printf("Prima del fork: x = %d\n", x);

    pid_t pid = fork();

    if (pid == 0) {
        // Processo figlio
        x += 10;
        printf("Figlio: x = %d\n", x);
    } else {
        // Processo padre
        x += 100;
        printf("Padre: x = %d\n", x);
    }

    return 0;
}
