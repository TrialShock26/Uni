include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int s) {
    printf("Ricevuto segnale %d\n", s);
}

int main(void) {
    sigset_t mask;
    signal(SIGUSR1, handler);

    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);

    // blocca SIGUSR1
    sigprocmask(SIG_BLOCK, &mask, NULL);
    printf("SIGUSR1 bloccato. PID=%d\n", getpid());

    printf("Manda più SIGUSR1 (es. kill -USR1 %d)\n", getpid());
    sleep(20);

    printf("Sblocco SIGUSR1\n");
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    pause(); // riceve ora il segnale

    return 0;
}
