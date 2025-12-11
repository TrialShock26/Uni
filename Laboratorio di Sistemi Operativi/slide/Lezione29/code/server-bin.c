#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUF_SIZE 1024

int main(void) {
    int listen_fd, conn_fd;
    struct sockaddr_in addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buf[BUF_SIZE];

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) { perror("socket"); exit(EXIT_FAILURE); }

    int opt = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);

    if (bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind"); exit(EXIT_FAILURE);
    }

    if (listen(listen_fd, 1) < 0) { perror("listen"); exit(EXIT_FAILURE); }

    printf("Server in ascolto sulla porta %d...\n", PORT);
    fflush(stdout);

    conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_len);
    if (conn_fd < 0) { perror("accept"); exit(EXIT_FAILURE); }

    printf("Connessione accettata.\n");

    ssize_t n = read(conn_fd, buf, BUF_SIZE - 1);
    if (n < 0) { perror("read"); exit(EXIT_FAILURE); }
    buf[n] = '\0';

    printf("Messaggio dal client: %s\n", buf);

    const char *reply = "Ciao dal server!\n";
    write(conn_fd, reply, strlen(reply));

    close(conn_fd);
    close(listen_fd);
    printf("Server termina.\n");
    return 0;
}
