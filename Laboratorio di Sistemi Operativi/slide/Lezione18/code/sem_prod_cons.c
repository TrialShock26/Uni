#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 8
#define N_PROD   2
#define N_CONS   2
#define N_ITEMS  10
#define KILL_PILL -1   // valore speciale per fermare i consumer

/* ---- buffer circolare condiviso ---- */
int buffer[BUF_SIZE];
int in_idx  = 0;    // prossima posizione di scrittura
int out_idx = 0;    // prossima posizione di lettura

/* ---- semafori ---- */
sem_t empty;   // conta gli slot liberi         (parte da BUF_SIZE)
sem_t full;    // conta gli elementi disponibili (parte da 0)
sem_t mutex;   // per proteggere buffer/in_idx/out_idx (parte da 1)

/* inserisce un elemento nel buffer */
void put_item(int item) {
    /* aspetta che ci sia spazio */
    sem_wait(&empty);

    /* sezione critica */
    sem_wait(&mutex);
    buffer[in_idx] = item;
    in_idx = (in_idx + 1) % BUF_SIZE;
    sem_post(&mutex);

    /* adesso c'è un elemento in più */
    sem_post(&full);
}

/* preleva un elemento dal buffer */
int get_item(void) {
    /* aspetta che ci sia almeno un elemento */
    sem_wait(&full);

    /* sezione critica */
    sem_wait(&mutex);
    int item = buffer[out_idx];
    out_idx = (out_idx + 1) % BUF_SIZE;
    sem_post(&mutex);

    /* adesso c'è uno slot libero in più */
    sem_post(&empty);

    return item;
}

/* ---- thread produttore ---- */
void* producer(void* arg) {
    for (int i = 0; i < N_ITEMS; i++) {
        put_item(i);                  // produce solo i numeri 0..N_ITEMS-1
        printf("[P] produced %d\n", i);
        usleep(10000);
    }
    return NULL;
}

/* ---- thread consumatore ---- */
void* consumer(void* arg) {
    long id = (long)arg;
    for (;;) {
        int item = get_item();
        if (item == KILL_PILL) {
            printf("   [C%ld] received KILL_PILL — exiting\n", id);
            break;
        }
        printf("   [C%ld] consumed %d\n", id, item);
        usleep(15000);
    }
    return NULL;
}

int main(void) {
    pthread_t prod[N_PROD], cons[N_CONS];

    /* inizializzo i semafori
       pshared = 0 → tra thread dello stesso processo */
    sem_init(&empty, 0, BUF_SIZE);   // buffer inizialmente vuoto → tutti gli slot liberi
    sem_init(&full,  0, 0);          // nessun elemento da consumare
    sem_init(&mutex, 0, 1);          // semaforo binario (come un mutex)

    /* creo i produttori */
    for (long i = 0; i < N_PROD; i++)
        pthread_create(&prod[i], NULL, producer, NULL);

    /* creo i consumatori */
    for (long i = 0; i < N_CONS; i++)
        pthread_create(&cons[i], NULL, consumer, (void*)i);

    /* aspetto che i produttori finiscano */
    for (int i = 0; i < N_PROD; i++)
        pthread_join(prod[i], NULL);

    /* i produttori hanno finito:
       metto UNA KILL_PILL per ogni consumer */
    for (int i = 0; i < N_CONS; i++)
        put_item(KILL_PILL);

    /* aspetto che i consumer terminino */
    for (int i = 0; i < N_CONS; i++)
        pthread_join(cons[i], NULL);

    /* distruggo i semafori */
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
