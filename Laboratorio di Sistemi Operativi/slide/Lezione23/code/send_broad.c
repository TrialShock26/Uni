#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 5000
#define BROADCAST_ADDR "255.255.255.255" //limited broadcast

int main() {
    int sock;
    struct sockaddr_in addr;
    char *msg = "Hello broadcast!";

    // 1. Crea socket UDP
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    // 2. Abilita il broadcast
    int yes = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes)) < 0) {
        perror("SO_BROADCAST");
        exit(1);
    }

    // 3. Imposta indirizzo broadcast destinazione
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(BROADCAST_ADDR);

    // 4. Invia periodicamente
    while (1) {
        if (sendto(sock, msg, strlen(msg), 0,
                   (struct sockaddr*)&addr, sizeof(addr)) < 0) {
            perror("sendto");
            exit(1);
        }
        printf("Inviato broadcast: %s\n", msg);
        sleep(1);
    }

    return 0;
}
