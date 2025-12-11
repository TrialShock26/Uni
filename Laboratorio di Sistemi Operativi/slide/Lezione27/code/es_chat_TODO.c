#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define BUF 256

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in local_addr, peer_addr;
    char buf[BUF];

    if (argc != 4) {
        fprintf(stderr, "Uso: %s <PORTA_LOCALE> <IP_PEER> <PORTA_PEER>\n", argv[0]);
        exit(1);
    }

    // Socket UDP
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) { perror("socket"); exit(1); }

    // Bind sulla porta locale
    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family      = AF_INET;
    local_addr.sin_port        = htons(atoi(argv[1]));
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock, (struct sockaddr *)&local_addr, sizeof(local_addr)) < 0) {
        perror("bind");
        exit(1);
    }

    // Indirizzo del peer
    memset(&peer_addr, 0, sizeof(peer_addr));
    peer_addr.sin_family = AF_INET;
    peer_addr.sin_port   = htons(atoi(argv[3]));
    if (inet_pton(AF_INET, argv[2], &peer_addr.sin_addr) <= 0) {
        perror("inet_pton");
        exit(1);
    }

    printf("Chat UDP\n");
    printf("Porta locale: %s, peer %s:%s\n", argv[1], argv[2], argv[3]);
    printf("Scrivi e premi invio per mandare messaggi.\n");

    while (1) {
        fd_set set;
        FD_ZERO(&set);

        // TODO: aggiungere stdin all'insieme
        // FD_SET(...);

        // TODO: aggiungere la socket all'insieme
        // FD_SET(...);

        int maxfd = sock;  // stdin = 0 → max è sock

        // TODO: completare select(maxfd+1, &set, NULL, NULL, NULL)
        // if (select( ... ) < 0) {
        if (select(/* TODO: numero fd           */
                   /* TODO: readfds (set)       */
                   /* TODO: writefds=NULL       */
                   /* TODO: exceptfds=NULL      */
                   /* TODO: timeout=NULL        */) < 0) {
            perror("select");
            break;
        }

        // Dati da tastiera: invia al peer
        if (/* TODO: controllare se stdin è pronto */) {
            int n = read(0, buf, BUF);
            if (n <= 0) {
                printf("EOF su stdin, esco.\n");
                break;
            }
            // TODO: inviare n byte al peer con sendto()
            // sendto(sock, buf, n, 0, ...);
        }

        // Dati dalla socket: stampa "lui dice: ..."
        if (/* TODO: controllare se socket è pronta */) {
            struct sockaddr_in from;
            socklen_t fromlen = sizeof(from);

            // TODO: ricevere dati dalla socket con recvfrom()
            // int n = recvfrom(sock, buf, BUF, 0, ...);

            int n = recvfrom(sock, buf, BUF, 0,
                             (struct sockaddr *)&from, &fromlen);

            if (n < 0) {
                perror("recvfrom");
                break;
            }
            write(1, "lui dice: ", 10);
            write(1, buf, n);
        }
    }

    close(sock);
    return 0;
}
