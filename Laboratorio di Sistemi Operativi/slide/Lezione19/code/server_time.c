#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define SOCKET_PATH "/tmp/time_socket"

void gestisci(int sd);

int main(void) {
    int listen_sd, connect_sd;
    struct sockaddr_un my_addr, client_addr;
    socklen_t client_len;

    // Crea il socket locale
    if ((listen_sd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Imposta l'indirizzo del server
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sun_family = AF_LOCAL;
    strncpy(my_addr.sun_path, SOCKET_PATH, sizeof(my_addr.sun_path) - 1);

    // Rimuove eventuale socket precedente
    unlink(SOCKET_PATH);

    // Effettua il bind
    if (bind(listen_sd, (struct sockaddr*)&my_addr, sizeof(my_addr)) < 0) {
        perror("bind");
        close(listen_sd);
        exit(EXIT_FAILURE);
    }

    // Mette il socket in ascolto
    if (listen(listen_sd, 5) < 0) {
        perror("listen");
        close(listen_sd);
        exit(EXIT_FAILURE);
    }

    printf("Server in ascolto su %s ...\n", SOCKET_PATH);

    // Ciclo principale: accetta connessioni e serve i client
    while (1) {
        client_len = sizeof(client_addr);
        connect_sd = accept(listen_sd, (struct sockaddr*)&client_addr, &client_len);
        if (connect_sd < 0) {
            perror("accept");
            continue;
        }

        printf("Nuova connessione accettata.\n");
        gestisci(connect_sd);
        close(connect_sd);
    }

    close(listen_sd);
    unlink(SOCKET_PATH);
    return 0;
}

void gestisci(int sd) {
    char buffer[26];
    time_t ora;

    time(&ora);
    ctime_r(&ora, buffer); // converte in stringa leggibile

    printf("Invio ora al client: %s", buffer);
    write(sd, buffer, strlen(buffer));
}
