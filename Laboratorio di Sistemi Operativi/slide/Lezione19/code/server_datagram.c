#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SOCK_PATH "/tmp/local_dgram"

int main(void) {
    int sfd;
    struct sockaddr_un addr, src;
    char buf[100];
    socklen_t slen = sizeof(src);

    // Crea socket datagram locale
    sfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if (sfd == -1) { perror("socket"); return 1; }

    // Associa un path al socket (bind)
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_LOCAL;
    strcpy(addr.sun_path, SOCK_PATH);
    unlink(SOCK_PATH);
    if (bind(sfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind"); return 1;
    }

    printf("Server pronto su %s\n", SOCK_PATH);

    // Attende un messaggio
    ssize_t n = recvfrom(sfd, buf, sizeof(buf) - 1, 0,
                         (struct sockaddr*)&src, &slen);
    if (n == -1) { perror("recvfrom"); return 1; }
    buf[n] = '\0';

    printf("Ricevuto: \"%s\"\n", buf);

    // Invia una risposta
    const char *msg = "OK dal server";
    sendto(sfd, msg, strlen(msg), 0, (struct sockaddr*)&src, slen);

    close(sfd);
    unlink(SOCK_PATH);
    return 0;
}
