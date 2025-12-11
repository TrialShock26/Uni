// server multithread TCP che fa echo
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>

#define PORT    5201
#define BACKLOG 8

static void *handle_client(void *arg) {
    int fd = *(int *)arg;
    free(arg);
    char buf[1024];
    for (;;) {
        ssize_t n = recv(fd, buf, sizeof(buf), 0);
        if (n == 0) break;
        if (n < 0) {
            if (errno == EINTR) continue;
            perror("recv");
            break;
        }
        ssize_t off = 0;
        while (off < n) {
            ssize_t w = send(fd, buf + off, (size_t)(n - off), MSG_NOSIGNAL);
            if (w < 0) {
                if (errno == EINTR) continue;
                perror("send");
                close(fd);
                return NULL;
            }
            off += w;
        }
    }
    close(fd);
    return NULL;
}

int main(void) {
    signal(SIGPIPE, SIG_IGN);

    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) { perror("socket"); return 1; }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) { perror("bind"); return 1; }
    if (listen(s, BACKLOG) < 0) { perror("listen"); return 1; }

    printf("Server in ascolto su 0.0.0.0:%d (thread per connessione)\n", PORT);

    for (;;) {
        int c = accept(s, NULL, NULL);
        if (c < 0) { if (errno == EINTR) continue; perror("accept"); continue; }

        int *fdp = malloc(sizeof(int));
        if (!fdp) {
            perror("malloc");
            close(c);
            continue;
        }
        *fdp = c;

        pthread_t tid;
        int rc = pthread_create(&tid, NULL, handle_client, fdp);
        if (rc != 0) {
            fprintf(stderr, "pthread_create: %s\n", strerror(rc));
            close(c);
            free(fdp);
            continue;
        }
        pthread_detach(tid);
    }
}
