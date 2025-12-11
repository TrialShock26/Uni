// cpu-eater.c
#include <stdio.h>

int main() {
    unsigned long long x = 0;
    while (1) {
        x++;               // loop infinito
        if (x % 1000000000 == 0)
            printf("x = %llu\n", x);
    }
    return 0;
}