// tcp_next_client_min.c
// tcp_next_client_min.c
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int s = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in srv = {0};
    srv.sin_family = AF_INET;
    srv.sin_port   = htons(5201);
    inet_pton(AF_INET, "127.0.0.1", &srv.sin_addr);

    connect(s, (struct sockaddr*)&srv, sizeof(srv));

    int x;
    printf("Inserisci un numero: ");

    if (scanf("%d", &x) != 1) {
        printf("Input non valido.\n");
        close(s);
        return 1;
    }

    uint32_t net_x = htonl((uint32_t)x);
    send(s, &net_x, sizeof(net_x), 0);

    uint32_t net_res;
    ssize_t r = recv(s, &net_res, sizeof(net_res), 0);

    if (r == sizeof(net_res)) {
        uint32_t res = ntohl(net_res);
        printf("Risposta dal server: %u\n", res);
    } else {
        printf("Errore durante recv\n");
    }

    close(s);
    return 0;
}
