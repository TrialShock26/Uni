#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 5000

int main() {
    int sock;
    struct sockaddr_in addr;
    char buffer[1024];

    // 1. Socket UDP
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    // 2. Permetti riuso porta
    int yes = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    // 3. Bind su tutte le interfacce
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(1);
    }

    printf("In ascolto broadcast UDP sulla porta %d…\n", PORT);

    // 4. Ricezione loop
    while (1) {
        int n = recv(sock, buffer, sizeof(buffer)-1, 0);
        if (n < 0) {
            perror("recv");
            exit(1);
        }
        buffer[n] = '\0';
        printf("Ricevuto: %s\n", buffer);
    }

    return 0;
}
