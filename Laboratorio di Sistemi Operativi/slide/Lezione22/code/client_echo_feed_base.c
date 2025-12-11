// client_echo_feedbase.c
// build:  cc -Wall -O2 client_echo_feed_base.c -o client
// run:    ./client 127.0.0.1 5000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXLINE 4096

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in servaddr;
    char sendbuf[MAXLINE];
    char recvbuf[MAXLINE];

    if (argc != 3) {
        fprintf(stderr, "usage: %s <server_ip> <port>\n", argv[0]);
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(atoi(argv[2]));

    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        perror("inet_pton");
        exit(1);
    }

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("connect");
        exit(1);
    }

    printf("Connesso al server %s:%s\n", argv[1], argv[2]);
    printf("Scrivi e premi invio...\n");

    while (1) {
        // (1) leggi da stdin
        if (fgets(sendbuf, sizeof(sendbuf), stdin) == NULL) {
            printf("EOF su stdin, esco.\n");
            break;
        }

        // (2) invia al server
        ssize_t n = send(sockfd, sendbuf, strlen(sendbuf), 0);
        if (n < 0) {
            perror("send");
            break;
        }

        // (3) *** BLOCCANTE ***
        n = recv(sockfd, recvbuf, sizeof(recvbuf), 0);
        if (n < 0) {
            perror("recv");
            break;
        }
        if (n == 0) {
            printf("Server ha chiuso.\n");
            break;
        }

        // (4) stampa la risposta
        write(STDOUT_FILENO, recvbuf, n);
    }

    close(sockfd);
    return 0;
}
