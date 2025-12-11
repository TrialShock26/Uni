#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/wait.h>

#define BUF 4

int main(void) {
    int fd[2];
    char buf[BUF];
    pipe(fd);

    if (fork() == 0) {                  // FIGLIO
        close(fd[1]);
        int p = fd[0];

        while (1) {
            fd_set s;
            FD_ZERO(&s);
            FD_SET(0, &s);
            FD_SET(p, &s);
            int m = p > 0 ? p : 0;

            if (select(m + 1, &s, NULL, NULL, NULL) <= 0)
                break;

            if (FD_ISSET(p, &s)) {      // dati dal padre (pipe)
                int n = read(p, buf, BUF - 1);
                if (n <= 0) break;
                buf[n] = '\0';
                printf("padre: %s", buf);
            }
            if (FD_ISSET(0, &s)) {      // dati letti dal figlio da stdin
                int n = read(0, buf, BUF - 1);
                if (n <= 0) break;
                buf[n] = '\0';
                printf("figlio: %s", buf);
            }
            fflush(stdout);
        }
        return 0;

    } else {                            // PADRE
        close(fd[0]);
        int p = fd[1];

        while (1) {
            fd_set s;
            FD_ZERO(&s);
            FD_SET(0, &s);

            if (select(1, &s, NULL, NULL, NULL) <= 0)
                break;

            if (FD_ISSET(0, &s)) {
                int n = read(0, buf, BUF - 1);
                if (n <= 0) break;
                buf[n] = '\0';
                write(p, buf, n);       // manda al figlio
            }
        }
        close(p);
        wait(NULL);
    }
}
