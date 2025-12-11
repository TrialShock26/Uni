#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <time.h>
#include <string.h>

#define MAX_BUF 256

int main(void) {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        /* FIGLIO */
        // TODO: chiudere l'estremità di scrittura della pipe (fd[1])

        int pipe_fd = fd[0];
        int pipe_closed = 0;
        char buf[MAX_BUF];

        while (1) {
            fd_set readfds;
            FD_ZERO(&readfds);

            // TODO: aggiungere pipe_fd al set
            // TODO: aggiungere stdin (fd 0) al set

            int maxfd = pipe_fd > 0 ? pipe_fd : 0;

            int ret = select(maxfd + 1, &readfds, NULL, NULL, NULL);
            if (ret < 0) {
                perror("select");
                exit(EXIT_FAILURE);
            }

            // Controllo pipe
            if (FD_ISSET(pipe_fd, &readfds)) {
                ssize_t n = read(pipe_fd, buf, sizeof(buf) - 1);
                if (n > 0) {
                    buf[n] = '\0';
                    printf("[PADRE] %s", buf);
                } else if (n == 0) {
                    // TODO: gestire EOF sulla pipe (padre ha chiuso)
                    // impostare pipe_closed = 1 e chiudere pipe_fd
                }
            }

            // Controllo tastiera (stdin = 0)
            if (FD_ISSET(0, &readfds)) {
                if (fgets(buf, sizeof(buf), stdin) == NULL) {
                    // EOF su stdin (CTRL+D): possiamo decidere di ignorare o uscire solo se pipe chiusa
                    if (pipe_closed) {
                        printf("EOF da tastiera e pipe chiusa: il figlio termina.\n");
                        break;
                    } else {
                        printf("EOF da tastiera, ma pipe ancora aperta.\n");
                        continue;
                    }
                } else {
                    // TODO: se l'utente digita "quit\n", uscire dal ciclo (se pipe chiusa)
                    // altrimenti stampare come [UTENTE] <linea>
                }
            }

            // Se pipe chiusa e abbiamo già ricevuto "quit", uscire (gestire nella logica sopra)
        }

        // TODO: eventuali chiusure finali
        exit(EXIT_SUCCESS);

    } else {
        /* PADRE */
        // TODO: chiudere l'estremità di lettura della pipe (fd[0])

        int pipe_fd = fd[1];

        // inizializzare rand
        srand(time(NULL) ^ getpid());

        for (int i = 1; i <= 10; i++) {
            int delay = (rand() % 5) + 1; // tra 1 e 5 secondi
            sleep(delay);

            char msg[MAX_BUF];
            snprintf(msg, sizeof(msg), "Messaggio %d dal padre\n", i);

            // TODO: scrivere msg sulla pipe
        }

        // TODO: chiudere la pipe
        // TODO: attendere il figlio con wait(NULL)

        printf("Padre termina.\n");
        exit(EXIT_SUCCESS);
    }
}
