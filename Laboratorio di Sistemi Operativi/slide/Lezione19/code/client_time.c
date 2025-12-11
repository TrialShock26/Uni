#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/time_socket"

int main(void) {
    int sd;
    struct sockaddr_un srv_addr;
    char msg[100];

    // Crea socket
    if ((sd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Imposta indirizzo del server
    memset(&srv_addr, 0, sizeof(srv_addr));
    srv_addr.sun_family = AF_LOCAL;
    strncpy(srv_addr.sun_path, SOCKET_PATH, sizeof(srv_addr.sun_path) - 1);

    // Connessione al server
    if (connect(sd, (struct sockaddr*)&srv_addr, sizeof(srv_addr)) < 0) {
        perror("connect");
        close(sd);
        exit(EXIT_FAILURE);
    }

    // Riceve e stampa l'ora
    ssize_t n = read(sd, msg, sizeof(msg) - 1);
    if (n > 0) {
        msg[n] = '\0';
        printf("Ora ricevuta dal server: %s", msg);
    } else {
        perror("read");
    }

    close(sd);
    return 0;
}
