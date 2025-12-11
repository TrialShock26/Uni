#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <arpa/inet.h>  // per htonl / ntohl

#define SOCKET_PATH "/tmp/array_bin.sock"

int main(void) {
    int listen_sd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (listen_sd < 0) { perror("socket"); exit(1); }

    struct sockaddr_un addr = {0};
    addr.sun_family = AF_LOCAL;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path)-1);
    unlink(SOCKET_PATH);

    if (bind(listen_sd, (struct sockaddr*)&addr, sizeof(addr)) < 0) { perror("bind"); exit(1); }
    listen(listen_sd, 1);
    int sd = accept(listen_sd, NULL, NULL);

    // --- Legge prima la dimensione ---
    uint32_t n_net, n;
    read(sd, &n_net, sizeof(n_net));
    n = ntohl(n_net);  // converte in ordine host

    printf("Server: mi aspetto %u numeri\n", n);
    uint32_t *vals = malloc(n * sizeof(uint32_t));

    // --- Legge gli elementi uno a uno ---
    for (uint32_t i = 0; i < n; i++) {
        uint32_t v_net;
        read(sd, &v_net, sizeof(v_net));
        vals[i] = ntohl(v_net);
    }

    printf("Server ha ricevuto: ");
    for (uint32_t i = 0; i < n; i++) printf("%u ", vals[i]);
    printf("\n");

    free(vals);
    close(sd);
    close(listen_sd);
    unlink(SOCKET_PATH);
    return 0;
}
