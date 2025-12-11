#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/* Thread worker */
void *worker(void *arg) {
    int oldstate;

    /* disabilito la cancellazione */
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate);
    printf("[thread] cancellazione disabilitata\n");

    printf("[thread] premere INVIO per permettere la cancellazione...\n");
    getchar();  // attende input da tastiera

    /* riabilito la cancellazione */
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);
    printf("[thread] cancellazione abilitata, ora posso essere terminato\n");

    /* loop infinito con punto di cancellazione */
    while (1) {
        printf("[thread] lavoro...\n");
        sleep(1);
        pthread_testcancel();  // punto di cancellazione
    }

    return NULL;
}

int main(void) {
    pthread_t tid;

    pthread_create(&tid, NULL, worker, NULL);

    /* prova a cancellare periodicamente il thread */
    while (1) {
        sleep(2);
        printf("[main] provo a cancellare il thread...\n");

        if (pthread_cancel(tid) == 0) {
            printf("[main] richiesta di cancellazione inviata\n");
            if (pthread_join(tid, NULL) == 0) {
                printf("[main] il thread è stato cancellato\n");
                break;
            }
        } else {
            printf("[main] thread ancora attivo\n");
        }
    }

    return 0;
}
