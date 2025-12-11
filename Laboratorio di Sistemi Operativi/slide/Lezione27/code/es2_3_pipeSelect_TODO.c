#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <string.h>

int main(void) {
    int p[2];
    pipe(p);

    if (fork() == 0) {          // FIGLIO
        close(p[1]);
        char buf[64];

        while (1) {
            fd_set set;
            FD_ZERO(&set);

            // TODO: aggiungere stdin e la pipe al set
            // FD_SET(...);
            // FD_SET(...);

            int maxfd = (p[0] > 0) ? p[0] : 0;

            if (select(/*TODO: aggiungere gli argomenti di select */) <= 0)
                break;

            // TODO: se ci sono dati sulla pipe, leggerli e stampare "PIPE: ..."
            // TODO: se ci sono dati su stdin, leggerli e stampare "STDIN: ..."

        }
    } else {                    // PADRE
        close(p[0]);
        char msg[] = "ping dal padre\n";

        for (int i = 0; i < 3; i++) {
            write(p[1], msg, strlen(msg));
            sleep(2);
        }
        close(p[1]);
        sleep(5);
    }
    return 0;
}
