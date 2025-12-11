// server_fork_nz.c — server TCP concorrente (no zombie)
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define PORT    5201
#define BACKLOG 8

// handler: raccoglie tutti i figli terminati
static void reap(int sig) {
    (void)sig;
    while (waitpid(-1, NULL, WNOHANG) > 0) {}
}

static void handle_client(int fd) {
    char buf[1024];
    for (;;) {
        ssize_t n = recv(fd, buf, sizeof(buf), 0);
        if (n == 0) break;
        if (n < 0) { if (errno == EINTR) continue; perror("recv"); break; }
        ssize_t off = 0;
        while (off < n) {
            ssize_t w = send(fd, buf + off, (size_t)(n - off), 0);
            if (w < 0) { if (errno == EINTR) continue; perror("send"); close(fd); _exit(1); }
            off += w;
        }
    }
    close(fd);
    _exit(0);
}

int main(void) {
    // installa SIGCHLD handler (SA_RESTART riavvia accept/recv interrotti)
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = reap;
    sa.sa_flags   = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGCHLD, &sa, NULL);

    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) { perror("socket"); return 1; }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) { perror("bind"); return 1; }
    if (listen(s, BACKLOG) < 0) { perror("listen"); return 1; }

    printf("Server in ascolto su 0.0.0.0:%d (fork per connessione, no zombie)\n", PORT);

    for (;;) {
        int c = accept(s, NULL, NULL);
        if (c < 0) { if (errno == EINTR) continue; perror("accept"); continue; }

        pid_t pid = fork();
        if (pid < 0) { perror("fork"); close(c); continue; }

        if (pid == 0) {           // FIGLIO
            close(s);
            handle_client(c);     // non ritorna
        }
        // PADRE
        close(c);
    }
}
