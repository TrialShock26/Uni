#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SOCK_PATH "/tmp/local_dgram"

int main(void) {
    int cfd;
    struct sockaddr_un srv, cli;
    char buf[100];
    ssize_t n;

    // Crea socket datagram locale
    cfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if (cfd == -1) { perror("socket"); return 1; }

    // Crea un indirizzo univoco per il client
    memset(&cli, 0, sizeof(cli));
    cli.sun_family = AF_LOCAL;
    snprintf(cli.sun_path, sizeof(cli.sun_path),
             "/tmp/client_%d", getpid());
    unlink(cli.sun_path);
    if (bind(cfd, (struct sockaddr*)&cli, sizeof(cli)) == -1) {
        perror("bind client"); return 1;
    }

    // Imposta indirizzo del server
    memset(&srv, 0, sizeof(srv));
    srv.sun_family = AF_LOCAL;
    strcpy(srv.sun_path, SOCK_PATH);

    // Invia messaggio
    const char *msg = "Ciao dal client!";
    sendto(cfd, msg, strlen(msg), 0,
           (struct sockaddr*)&srv, sizeof(srv));

    // Attende la risposta
    n = recvfrom(cfd, buf, sizeof(buf) - 1, 0, NULL, NULL);
    if (n == -1) { perror("recvfrom"); return 1; }
    buf[n] = '\0';
    printf("Risposta del server: \"%s\"\n", buf);

    close(cfd);
    unlink(cli.sun_path);
    return 0;
}
