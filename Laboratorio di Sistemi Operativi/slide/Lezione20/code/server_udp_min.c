#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
    int s;
    struct sockaddr_in addr = {0};
    char buf[1024];

    s = socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(5200);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(s, (struct sockaddr *)&addr, sizeof(addr));

    while (1) {
        struct sockaddr_in from = {0};
        socklen_t flen = sizeof(from);

        int n = recvfrom(s, buf, sizeof(buf), 0,
                         (struct sockaddr *)&from, &flen);
		printf("server: ricevuti %d byte\n",n);

        sendto(s, buf, n, 0,
               (struct sockaddr *)&from, flen);
    }

    close(s);
}
