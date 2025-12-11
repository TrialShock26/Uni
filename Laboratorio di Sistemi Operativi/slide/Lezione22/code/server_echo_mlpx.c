// server_echo_mlpx.c — Echo server con select()
// compila: cc -Wall -Wextra -O2 server_echo_mlpx.c -o server_mlpx
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>

#define PORT        8080
#define MAXLINE     4096

int main(void) {
    int listenfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    fd_set allset, rset;        // allset = insieme stabile; rset = copia per select
    int client[FD_SETSIZE];     // come nelle slide: elenco fd attivi o -1 se libero
    int maxfd, maxi = -1;       // maxfd = fd più alto; maxi = ultimo indice usato in client[]
    int i, nready;

    // 1) listening socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) { perror("socket"); exit(1); }

    int one = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(PORT);

    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind"); exit(1);
    }
    if (listen(listenfd, 128) < 0) {
        perror("listen"); exit(1);
    }

    // 2) inizializza struttura per select
    for (i = 0; i < FD_SETSIZE; i++) client[i] = -1;
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);
    maxfd = listenfd;

    // 3) loop principale
    for (;;) {
        rset = allset;                        // select consuma i set: usa una copia
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if (nready < 0) {
            if (errno == EINTR) continue;
            perror("select"); exit(1);
        }

        // 3a) nuova connessione?
        if (FD_ISSET(listenfd, &rset)) {
            len = sizeof(cliaddr);
            connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len);
            if (connfd < 0) { perror("accept"); continue; }

            // inserisci connfd nel primo posto libero di client[]
            for (i = 0; i < FD_SETSIZE; i++) {
                if (client[i] < 0) { client[i] = connfd; break; }
            }
            if (i == FD_SETSIZE) {            // nessun posto libero
                fprintf(stderr, "Troppe connessioni (FD_SETSIZE)\n");
                close(connfd);
            } else {
                FD_SET(connfd, &allset);      // monitora il nuovo fd
                if (connfd > maxfd) maxfd = connfd;
                if (i > maxi) maxi = i;
            }
            if (--nready <= 0) continue;      // nessun altro fd pronto
        }

        // 3b) dati dai client esistenti?
        for (i = 0; i <= maxi; i++) {
            int sockfd = client[i];
            if (sockfd < 0) continue;
            if (FD_ISSET(sockfd, &rset)) {
                char buf[MAXLINE];
                ssize_t n = recv(sockfd, buf, sizeof(buf), 0);
                if (n < 0) {                  // errore di lettura
                    perror("recv");
                    close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                } else if (n == 0) {          // client ha chiuso → rimuovi
                    close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                } else {                       // echo
                    ssize_t off = 0;
                    while (off < n) {
                        ssize_t w = send(sockfd, buf + off, (size_t)(n - off), 0);
                        if (w < 0) { perror("send"); break; }
                        off += w;
                    }
                }
                if (--nready <= 0) break;     // gestiti tutti i pronti
            }
        }
    }
}
