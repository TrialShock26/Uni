// whois_scheletro.c
// Scheletro da completare – mini client WHOIS via TCP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define WHOIS_SERVER "whois.iana.org"
#define WHOIS_PORT   "43"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s dominio\n", argv[0]);
        return 1;
    }

    const char *query = argv[1];   // dominio da cercare
    int sock;

    // -------------------------
    // TODO 1: usare getaddrinfo() per risolvere WHOIS_SERVER:WHOIS_PORT
    // Suggerimento:
    //   struct addrinfo hints, *res;
    //   memset(&hints, 0, sizeof(hints));
    //   hints.ai_family = AF_UNSPEC;
    //   hints.ai_socktype = SOCK_STREAM;
    //   getaddrinfo(WHOIS_SERVER, WHOIS_PORT, &hints, &res);
    // -------------------------

    struct addrinfo hints, *res;
    // >>> COMPLETARE: risolvere indirizzo WHOIS <<<


    // -------------------------
    // TODO 2: creare la socket con socket(res->ai_family, ...)
    // -------------------------

    // >>> COMPLETARE: sock = socket(...) <<<



    // -------------------------
    // TODO 3: connettersi al server WHOIS con connect()
    // -------------------------

    // >>> COMPLETARE: connect(sock, res->ai_addr, res->ai_addrlen) <<<


    freeaddrinfo(res);

    // -------------------------
    // TODO 4: inviare la stringa "<dominio>\r\n" al server WHOIS
    //
    // Suggerimento:
    //   char buf[256];
    //   snprintf(buf, sizeof(buf), "%s\r\n", query);
    //   send(sock, buf, strlen(buf), 0);
    // -------------------------

    // >>> COMPLETARE: inviare la query <<<




    // -------------------------
    // TODO 5: leggere la risposta WHOIS e stamparla
    //
    // usare recv() in un loop finché non restituisce 0
    // -------------------------

    // >>> COMPLETARE: ciclo recv() e printf <<<


    close(sock);
    return 0;
}
