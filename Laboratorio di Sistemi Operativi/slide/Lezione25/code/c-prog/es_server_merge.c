#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF 512   // unico buffer grande

int main(void) {
    int sockfd;
    struct sockaddr_in serv, cli;
    socklen_t len = sizeof(cli);

    char buf[BUF];
    int count = 0;     // quanti messaggi abbiamo ricevuto
    int pos = 0;       // dove concatenare

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&serv, 0, sizeof(serv));
    serv.sin_family      = AF_INET;
    serv.sin_port        = htons(5000);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));

    printf("Server UDP in ascolto...\n");

    while (1) {
        ssize_t n = recvfrom(sockfd, buf + pos, BUF - pos - 1,
                             0, (struct sockaddr*)&cli, &len);
        if (n <= 0) continue;

        buf[pos + n] = '\0';

        printf("Ricevuto: \"%s\"\n", buf + pos);

        if (count == 0) {
            // Abbiamo ricevuto il primo messaggio
            pos = strlen(buf);   // pos = fine del primo messaggio
            buf[pos++] = '-';    // aggiungi "-"
            buf[pos] = '\0';
            count = 1;
        } else {
            // Abbiamo ricevuto il secondo messaggio, buf contiene "msg1-msg2"
            sendto(sockfd, buf, strlen(buf), 0,
                   (struct sockaddr*)&cli, len);
            printf("Inviato: \"%s\"\n", buf);

            // reset
            count = 0;
            pos = 0;
            buf[0] = '\0';
        }
    }

    close(sockfd);
    return 0;
}
