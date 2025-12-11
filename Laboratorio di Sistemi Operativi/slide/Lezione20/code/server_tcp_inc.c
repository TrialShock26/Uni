//server_tcp_inc_min.c
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int s = -1;    // listening socket

void handler(int sig) {
    (void)sig;
    if (s >= 0) {
        shutdown(s, SHUT_RDWR);   // forza accept a ritornare
    }
}

int main(void) {

    signal(SIGINT, handler);

    s = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {0};
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(5201);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(s, (struct sockaddr*)&addr, sizeof(addr));
    listen(s, 1);

    printf("[server] in ascolto (Ctrl-C per uscire)\n");

    while (1) {
        int c = accept(s, NULL, NULL);
        if (c < 0) {
            // probabile uscita causata da shutdown()
            break;
        }

        uint32_t net_x;
        ssize_t r = recv(c, &net_x, sizeof(net_x), 0);

        if (r == sizeof(net_x)) {
            uint32_t x = ntohl(net_x);
            uint32_t next = x + 1;
            uint32_t net_next = htonl(next);
            send(c, &net_next, sizeof(net_next), 0);
        }

        close(c);
    }

    close(s);
    return 0;
}
