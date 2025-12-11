#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
    int s;
    struct sockaddr_in addr = {0};
    char buf[1024] = "ciao";

    s = socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port   = htons(5200);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    
	printf("invio al server: %s\n", buf);
    sendto(s, buf, strlen(buf), 0,
           (struct sockaddr *)&addr, sizeof(addr));

    int n = recvfrom(s, buf, sizeof(buf), 0, NULL, NULL);
	buf[n] = '\0';
    /* ... usa buf ... */
	printf("ricevuto dal server: %s\n", buf);

    close(s);
}
