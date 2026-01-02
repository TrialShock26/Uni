#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <hostname-server>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *hostname = argv[1];

    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int err = getaddrinfo(hostname, "5000", &hints, &res);
    if (err != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
        exit(EXIT_FAILURE);
    }

    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0) { perror("socket"); exit(EXIT_FAILURE); }

    if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
        perror("connect"); exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);

    const char *msg = "Ciao dal client!\n";
    write(sockfd, msg, strlen(msg));

    char buf[BUF_SIZE];
    ssize_t n = read(sockfd, buf, BUF_SIZE - 1);
    if (n < 0) { perror("read"); exit(EXIT_FAILURE); }
    buf[n] = '\0';

    printf("Risposta dal server: %s\n", buf);

    close(sockfd);
    return 0;
}
