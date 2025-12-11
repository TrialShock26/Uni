#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>

int main(void) {
    fd_set readfds;
    struct timeval tv;
    int nfds = STDIN_FILENO + 1;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    tv.tv_sec  = 2;
    tv.tv_usec = 500000;   // 2.5 s

    int n = select(nfds, &readfds, NULL, NULL, &tv);
    if (n < 0) {
        if (errno == EINTR) { /* ripetere se necessario */ }
        perror("select");
        return 1;
    } else if (n == 0) {
        printf("Timed out.\n");
    } else if (FD_ISSET(STDIN_FILENO, &readfds)) {
        printf("Input disponibile (dopo Invio).\n");
        // Esempio: leggere qualcosa
        char buf[128];
        ssize_t r = read(STDIN_FILENO, buf, sizeof buf);
        if (r > 0) write(STDOUT_FILENO, buf, (size_t)r);
    }
    return 0;
}

