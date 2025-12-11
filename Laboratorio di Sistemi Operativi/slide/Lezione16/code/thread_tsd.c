#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* Chiave globale per i dati specifici del thread */
pthread_key_t chiave;

/* Funzione eseguita da ogni thread */
void *worker(void *arg) {
    int *id = (int *)arg;   // id passato dal main
    int *val = malloc(sizeof(int));
    *val = *id * 10;        // calcolo un valore solo per questo thread

    /* associo il valore alla chiave (specifico per thread) */
    pthread_setspecific(chiave, val);

    /* recupero il valore dalla chiave e lo stampo */
    int *mio_val = pthread_getspecific(chiave);
    printf("[thread %d] valore specifico = %d\n", *id, *mio_val);

    free(val);  // libero la memoria
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    /* creo la chiave globale */
    pthread_key_create(&chiave, NULL);

    /* creo due thread, ciascuno con un proprio id */
    pthread_create(&t1, NULL, worker, &id1);
    pthread_create(&t2, NULL, worker, &id2);

    /* attendo la fine dei thread */
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    /* elimino la chiave */
    pthread_key_delete(chiave);

    return 0;
}
