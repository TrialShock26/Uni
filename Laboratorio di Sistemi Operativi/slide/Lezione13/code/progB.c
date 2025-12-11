include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("Sono il programma B, con PID %d\n", getpid());
    return 0;
}
