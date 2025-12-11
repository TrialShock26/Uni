// receiver_multicast.c

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
    struct ip_mreq mreq;
    char msgbuf[256];

    // Socket UDP
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }
	// Per permettere a più client di fare bind sullo stesso addrs
	int reuse = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));

    // Bind sulla porta (0.0.0.0:PORT)
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);

    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(1);
    }

    // Join del gruppo multicast
    mreq.imr_multiaddr.s_addr = inet_addr(GROUP);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                   &mreq, sizeof(mreq)) < 0) {
        perror("setsockopt - IP_ADD_MEMBERSHIP");
        exit(1);
    }

    // Ricezione
    while (1) {
        int n = recv(sock, msgbuf, sizeof(msgbuf)-1, 0);
        if (n < 0) {
            perror("recv");
            exit(1);
        }
        msgbuf[n] = '\0';
        printf("Ricevuto: %s\n", msgbuf);
    }

    return 0;
}
