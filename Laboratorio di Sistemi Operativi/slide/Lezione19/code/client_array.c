#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <arpa/inet.h>  // per htonl

#define SOCKET_PATH "/tmp/array_bin.sock"

int main(void) {
    int sd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (sd < 0) { perror("socket"); exit(1); }

    struct sockaddr_un addr = {0};
    addr.sun_family = AF_LOCAL;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path)-1);

    if (connect(sd, (struct sockaddr*)&addr, sizeof(addr)) < 0) { perror("connect"); exit(1); }

    uint32_t vals[] = {10, 20, 30, 40, 50};
    uint32_t n = sizeof(vals) / sizeof(vals[0]);

    // --- Invio dimensione ---
    uint32_t n_net = htonl(n);
    write(sd, &n_net, sizeof(n_net));

    // --- Invio valori convertiti ---
    for (uint32_t i = 0; i < n; i++) {
        uint32_t v_net = htonl(vals[i]);
        write(sd, &v_net, sizeof(v_net));
    }

    printf("Client ha inviato %u numeri\n", n);

    close(sd);
    return 0;
}
