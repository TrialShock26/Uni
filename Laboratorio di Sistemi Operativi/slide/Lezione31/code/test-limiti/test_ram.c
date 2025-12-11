// mem-eater_fixed.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Necessario per memset
#include <unistd.h>

#define BLOCK_SIZE (1024 * 1024) // 1 MB

int main() {
    size_t m = 0;
    while (1) {
        char *p = (char *)malloc(BLOCK_SIZE); // Alloca 1 MB
        
        if (!p) {
            perror("malloc failed");
            return 1;
        }

                // Scrive 1 MB di dati, forzando l'uso della RAM fisica
        memset(p, 'A', BLOCK_SIZE); 
        
        m++;
        printf("Allocated and used %zu MB\n", m);
        usleep(100000); 
    }
    return 0;
}