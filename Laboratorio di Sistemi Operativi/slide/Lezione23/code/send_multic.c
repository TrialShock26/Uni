// sender_multicast.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define GROUP "239.255.0.1"
#define PORT  5000

int main() {
    int sock;
    struct sockaddr_in addr;
    unsigned char ttl = 1;   // TTL = 1 → LAN locale

    // Socket UDP
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    // Imposta TTL multicast
    if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL,
                   &ttl, sizeof(ttl)) < 0) {
        perror("setsockopt - TTL");
        exit(1);
    }

    // Indirizzo multicast di destinazione
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(GROUP);

    // Loop di invio
    while (1) {
        char msg[128];
        sprintf(msg, "Ciao dalla VM multicast!");

        if (sendto(sock, msg, strlen(msg), 0,
                   (struct sockaddr *)&addr, sizeof(addr)) < 0) {
            perror("sendto");
            exit(1);
        }

        printf("Inviato: %s\n", msg);
        sleep(1);
    }

    return 0;
}
