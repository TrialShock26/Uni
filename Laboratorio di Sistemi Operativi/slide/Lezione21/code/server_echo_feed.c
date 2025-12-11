// server_echo_feed.c
// build:  cc -Wall -O2 server_echo_feed.c -o server
// run:    ./server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT     5000
#define MAXLINE  4096

int main(void) {
    int listenfd, connfd;
    struct sockaddr_in servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) { perror("socket"); exit(1); }

    int on = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(PORT);

    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind"); exit(1);
    }

    if (listen(listenfd, 1) < 0) {
        perror("listen"); exit(1);
    }

    printf("Server in ascolto su porta %d...\n", PORT);

    connfd = accept(listenfd, NULL, NULL);
    if (connfd < 0) { perror("accept"); exit(1); }

    printf("Client connesso.\n");

    time_t last = time(NULL);

    for (;;) {
        char buf[MAXLINE];

        // (1) prova a leggere senza bloccare
        ssize_t n = recv(connfd, buf, sizeof(buf), MSG_DONTWAIT);

        if (n > 0) {
            // echo
            send(connfd, buf, n, 0);

        } else if (n == 0) {
            // client chiuso
            printf("Client ha chiuso.\n");
            break;
        } else {
            // n < 0
            if (errno != EAGAIN && errno != EWOULDBLOCK) {
                // errore reale
                perror("recv");
                break;
            }
            // altrimenti → nessun dato, tutto normale
        }

        // (2) invio periodico ogni 10s
        time_t now = time(NULL);
        if (now - last >= 10) {
            const char *msg = "x\n";
            send(connfd, msg, strlen(msg), 0);
            last = now;
        }

        // (3) pausa minima per non saturare la CPU
        usleep(10000); // 10ms
    }

    close(connfd);
    close(listenfd);
    return 0;
}

