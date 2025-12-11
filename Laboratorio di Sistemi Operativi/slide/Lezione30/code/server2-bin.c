// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORTA 5000
#define BUFFER_SIZE 1024

int main(void) {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[BUFFER_SIZE];

    // Creazione socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Errore nella creazione della socket");
        exit(EXIT_FAILURE);
    }

    // Opzione per riusare subito la porta dopo la chiusura
    int opt = 1;
    if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("Errore in setsockopt");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    // Struttura indirizzo server
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;   // Ascolta su tutte le interfacce
    server_addr.sin_port = htons(PORTA);

    // Bind
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Errore nel bind");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_sock, 5) < 0) {
        perror("Errore nella listen");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    printf("Server in ascolto sulla porta %d...\n", PORTA);

    // Ciclo infinito: accetta più client uno dopo l'altro
    while (1) {
        client_len = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
        if (client_sock < 0) {
            perror("Errore in accept");
            // In un esercizio didattico possiamo continuare
            continue;
        }

        printf("Client connesso da %s:%d\n",
               inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port));

        // Esempio minimo di gestione: riceve un messaggio e stampa
        ssize_t n = read(client_sock, buffer, BUFFER_SIZE - 1);
        if (n > 0) {
            buffer[n] = '\0';
            printf("Messaggio dal client: %s\n", buffer);

            // Risposta semplice al client (se il client la legge, bene; altrimenti non dà fastidio)
            const char *reply = "OK dal server\n";
            write(client_sock, reply, strlen(reply));
        } else if (n == 0) {
            printf("Client ha chiuso la connessione.\n");
        } else {
            perror("Errore in read dal client");
        }

        // Chiudi la socket del client, torna ad accettare un nuovo client
        close(client_sock);
        printf("Connessione con il client terminata, in attesa di un nuovo client...\n");
    }

    // In pratica qui non si arriva mai
    close(server_sock);
    return 0;
}
