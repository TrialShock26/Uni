#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 8
#define N_PROD   2
#define N_CONS   2
#define N_ITEMS  10
#define KILL_PILL -1    // simbolo speciale: termina i consumer

typedef struct {
    int buf[BUF_SIZE];
    int in, out, count;
    pthread_mutex_t mtx;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
} bbuff_t;

/* --- Inizializzazione e distruzione --- */
void bbuff_init(bbuff_t *b) {
    b->in = 0;
    b->out = 0;
    b->count = 0;
    pthread_mutex_init(&b->mtx, NULL);
    pthread_cond_init(&b->not_full, NULL);
    pthread_cond_init(&b->not_empty, NULL);
}

void bbuff_destroy(bbuff_t *b) {
    pthread_mutex_destroy(&b->mtx);
    pthread_cond_destroy(&b->not_full);
    pthread_cond_destroy(&b->not_empty);
}

/* --- DA COMPLETARE DAGLI STUDENTI --- */
void put_item(bbuff_t *b, int item) {
    // TODO: proteggere con mutex
    // TODO: se pieno -> wait(not_full)
    // TODO: inserire item nel buffer
    // TODO: segnalare not_empty
}

int get_item(bbuff_t *b) {
    // TODO: proteggere con mutex
    // TODO: se vuoto -> wait(not_empty)
    // TODO: prelevare item
    // TODO: segnalare not_full
    return 0; // placeholder
}

/* --- Producer --- */
void* producer(void* arg) {
    bbuff_t *b = (bbuff_t*)arg;
    for (int i = 0; i < N_ITEMS; i++) {
        put_item(b, i);                 // produce solo il numero i
        printf("[P] produced %d\n", i);
        usleep(10000);                  // solo per rallentare un po’
    }
    return NULL;
}

/* --- Consumer --- */
void* consumer(void* arg) {
    bbuff_t *b = (bbuff_t*)arg;
    for (;;) {
        int item = get_item(b);
        if (item == KILL_PILL) {
            printf("   [C] received KILL_PILL — exiting\n");
            break;
        }
        printf("   [C] consumed %d\n", item);
        usleep(15000);
    }
    return NULL;
}

/* --- Main --- */
int main(void) {
    bbuff_t *bb = malloc(sizeof(bbuff_t));
    if (!bb) { perror("malloc"); exit(1); }
    bbuff_init(bb);

    pthread_t prod[N_PROD], cons[N_CONS];

    // Avvio i producer
    for (int i = 0; i < N_PROD; i++)
        pthread_create(&prod[i], NULL, producer, bb);

    // Avvio i consumer
    for (int i = 0; i < N_CONS; i++)
        pthread_create(&cons[i], NULL, consumer, bb);

    // Attendo che i producer finiscano
    for (int i = 0; i < N_PROD; i++)
        pthread_join(prod[i], NULL);

    // Metto una KILL_PILL per ogni consumer
    for (int i = 0; i < N_CONS; i++)
        put_item(bb, KILL_PILL);

    // Attendo che i consumer finiscano
    for (int i = 0; i < N_CONS; i++)
        pthread_join(cons[i], NULL);

    bbuff_destroy(bb);
    free(bb);

    return 0;
}
