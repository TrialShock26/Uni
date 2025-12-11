// mchat_scheletro.c
// Chat di gruppo via multicast UDP (scheletro da completare)
//
// Obiettivo: più processi eseguono questo programma.
// Tutti si iscrivono allo stesso gruppo multicast e:
//  - leggono dalla tastiera e mandano al gruppo
//  - stampano a video i messaggi ricevuti dal gruppo
//
// DA COMPLETARE:
//  - uso di select() per multiplexare stdin e socket
//  - invio con sendto()
//  - ricezione con recvfrom()
//
// Compilazione (esempio):
//   gcc -Wall -O2 mchat_scheletro.c -o mchat
//
// Esecuzione (default gruppo 239.1.2.3 porta 5000):
//   ./mchat
// oppure:
//   ./mchat 239.1.2.3 5000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
    const char *group = "239.1.2.3";  // gruppo multicast di default
    int port = 5000;                  // porta di default

    if (argc >= 2) group = argv[1];   // se passati da linea di comando...
    if (argc >= 3) port  = atoi(argv[2]);

    int sock;
    struct sockaddr_in addr;
    struct ip_mreq mreq;

    // 1. Creazione socket UDP
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 2. Permette a più processi di fare bind sulla stessa porta (utile nel lab)
    int reuse = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("SO_REUSEADDR");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // 3. Bind alla porta locale (accetta datagram su tutte le interfacce)
    memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port        = htons(port);

    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // 4. Join al gruppo multicast
    mreq.imr_multiaddr.s_addr = inet_addr(group);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);  // qualsiasi interfaccia

    if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                   &mreq, sizeof(mreq)) < 0) {
        perror("IP_ADD_MEMBERSHIP");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // 5. Abilita (opzionale) il loopback multicast:
    //    se a 1, il processo riceve anche i propri messaggi
    int loop = 1;
    if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_LOOP,
                   &loop, sizeof(loop)) < 0) {
        perror("IP_MULTICAST_LOOP");
        // non è critico, continuiamo lo stesso
    }

    printf("mchat (scheletro): gruppo %s, porta %d\n", group, port);
    printf("Scrivi un messaggio e premi Invio (Ctrl+D per uscire)\n");

    // Indirizzo del gruppo da usare in sendto()
    struct sockaddr_in mcast_addr;
    memset(&mcast_addr, 0, sizeof(mcast_addr));
    mcast_addr.sin_family = AF_INET;
    mcast_addr.sin_port   = htons(port);
    if (inet_pton(AF_INET, group, &mcast_addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(sock);
        exit(EXIT_FAILURE);
    }

    char buf[1024];

    // Ciclo principale: vogliamo leggere sia da stdin che dalla socket
    while (1) {
        fd_set rfds;
        int maxfd;

        // TODO 1: inizializzare il set di descrittori per select()
        //
        // Suggerimento:
        //   - azzera il set
        //   - aggiungi STDIN_FILENO (tastiera)
        //   - aggiungi 'sock' (socket UDP)
        //
        // Esempio:
        //   FD_ZERO(&rfds);
        //   FD_SET(STDIN_FILENO, &rfds);
        //   FD_SET(sock, &rfds);
        //
        // Poi calcola maxfd = max(sock, STDIN_FILENO) + 1;

        // >>> QUI COMPLETARE TODO 1 <<<





        // TODO 2: chiamare select() in modalità bloccante
        //
        //   int ret = select(maxfd, &rfds, NULL, NULL, NULL);
        //
        // Gestire il caso ret < 0 (errore) con perror e break;
        //
        // >>> QUI COMPLETARE TODO 2 <<<

        int ret = -1;  // placeholder, da sostituire con la vera select()

        if (ret < 0) {
            perror("select");
            break;
        }

        // Caso 1: c'è input da tastiera (STDIN) → inviare al gruppo multicast
        if (FD_ISSET(STDIN_FILENO, &rfds)) {
            if (!fgets(buf, sizeof(buf), stdin)) {
                // EOF (Ctrl+D): usciamo dal programma
                printf("EOF su stdin, esco.\n");
                break;
            }

            size_t len = strlen(buf);
            if (len > 0 && buf[len - 1] == '\n') {
                buf[len - 1] = '\0';
                len--;
            }
            if (len == 0) {
                // riga vuota: non mandiamo niente
            } else {
                // TODO 3: inviare il contenuto di buf al gruppo multicast
                //
                // Usare sendto() con:
                //   - descrittore: sock
                //   - buffer: buf
                //   - lunghezza: len
                //   - flags: 0
                //   - destinatario: (struct sockaddr *)&mcast_addr
                //   - lunghezza dest: sizeof(mcast_addr)
                //
                // Suggerimento:
                //   ssize_t n = sendto(...);
                //   controllare se n < 0 per eventuali errori
                //
                // >>> QUI COMPLETARE TODO 3 <<<


            }
        }

        // Caso 2: c'è un datagram pronto sulla socket → ricevere e stampare
        if (FD_ISSET(sock, &rfds)) {
            struct sockaddr_in src;
            socklen_t srclen = sizeof(src);

            // TODO 4: ricevere un datagram con recvfrom()
            //
            //   - buffer: buf
            //   - dimensione: sizeof(buf) - 1 (lascia spazio per '\0')
            //   - flags: 0
            //   - sorgente: (struct sockaddr *)&src
            //   - len sorgente: &srclen
            //
            // Dopo la recvfrom():
            //   - se n < 0: perror e break;
            //   - aggiungi '\0' in buf[n] per trattarlo come stringa
            //
            // >>> QUI COMPLETARE TODO 4 <<<

            ssize_t n = -1;  // placeholder, da sostituire con recvfrom()

            if (n < 0) {
                perror("recvfrom");
                break;
            }

            buf[n] = '\0';  // terminatore di stringa

            // Ricava l'IP sorgente in forma testuale
            char ipstr[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &src.sin_addr, ipstr, sizeof(ipstr));

            // Stampa: [ip] messaggio
            printf("[%s] %s\n", ipstr, buf);
        }
    }

    close(sock);
    return 0;
}
