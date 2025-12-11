#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>

#define PORTA 5000
#define BUFFER_SIZE 1024

// Funzione per gestire la connessione del client (eseguita dal processo figlio)
void handle_client(int client_sock, struct sockaddr_in client_addr) {
    char buffer[BUFFER_SIZE];
    
    printf("[PID %d] Client connesso da %s:%d\n", getpid(),
           inet_ntoa(client_addr.sin_addr),
           ntohs(client_addr.sin_port));

    // Simula una breve attività per mantenere il processo vivo
    sleep(10); 

    // Ricezione messaggio
    ssize_t n = read(client_sock, buffer, BUFFER_SIZE - 1);
    if (n > 0) {
        buffer[n] = '\0';
        printf("[PID %d] Messaggio ricevuto: %s\n", getpid(), buffer);
        
        // Risposta e chiusura immediata
        const char *reply = "OK, connessione in chiusura.\n";
        write(client_sock, reply, strlen(reply));
    } else if (n == 0) {
        printf("[PID %d] Client ha chiuso la connessione.\n", getpid());
    } else {
        perror("[PID %d] Errore in read");
    }

    close(client_sock);
    exit(EXIT_SUCCESS); // TERMINA IL PROCESSO FIGLIO
}

// Handler per i processi "zombie" (buona pratica per i server)
void sigchld_handler(int s) {
    while(waitpid(-1, NULL, WNOHANG) > 0);
}


int main(void) {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;

    // Configurazione per gestire i processi zombie
    struct sigaction sa;
    sa.sa_handler = sigchld_handler; 
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    
    // ... (Logica di creazione, bind e listen identica alla tua precedente) ...
    
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    // ... (omesse le verifiche di errore per brevità) ...
    int opt = 1;
    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORTA);

    bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_sock, 5); // Il backlog è ancora 5
    
    printf("Server [PID %d] in ascolto sulla porta %d...\n", getpid(), PORTA);

    // Ciclo di accettazione e fork
    while (1) {
        client_len = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
        if (client_sock < 0) {
            perror("Errore in accept");
            continue;
        }

        // === PUNTO CHIAVE: FORK ===
        pid_t pid = fork();

        if (pid < 0) {
            perror("Errore in fork. Limite PID raggiunto?");
            close(client_sock); 
        } else if (pid == 0) {
            // Processo Figlio: gestisce il client
            close(server_sock); 
            handle_client(client_sock, client_addr); 
            // La handle_client termina il figlio
        } else {
            // Processo Padre: chiude la socket del client e torna ad ascoltare
            printf("[PID %d] Processo figlio creato con PID %d.\n", getpid(), pid);
            close(client_sock); 
        }
    }

    close(server_sock);
    return 0;
}
