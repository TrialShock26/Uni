// correggi l'errore di questo codice
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

int sockfd;
struct sockaddr_in servaddr;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* sender(void* arg) {
    const char *msg1 = "ciao";
    const char *msg2 = "mondo";

    pthread_mutex_lock(&mtx);

    sendto(sockfd, msg1, strlen(msg1), 0,
           (struct sockaddr*)&servaddr, sizeof(servaddr));
    printf("sender: inviato '%s'\n", msg1);

    sendto(sockfd, msg2, strlen(msg2), 0,
           (struct sockaddr*)&servaddr, sizeof(servaddr));
    printf("sender: inviato '%s'\n", msg2);

    pthread_mutex_unlock(&mtx);
    return NULL;
}

void* receiver(void* arg) {
    char buf[256];
    pthread_mutex_lock(&mtx);

    ssize_t n = recvfrom(sockfd, buf, sizeof(buf)-1, 0, NULL, NULL);
    if (n > 0) {
        buf[n] = '\0';
        printf("receiver: ricevuto <%s>\n", buf);
    } else {
        perror("recvfrom");
    }

    pthread_mutex_unlock(&mtx);
    return NULL;
}

int main(void) {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(5000);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    pthread_t tsend, trecv;

    pthread_create(&trecv, NULL, receiver, NULL);
    pthread_create(&tsend, NULL, sender, NULL);

    pthread_join(tsend, NULL);
    pthread_join(trecv, NULL);

    close(sockfd);
    return 0;
}
