// readers_writers_esercizio.c
// Completare le sezioni ENTRY e EXIT del lettore.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex    = PTHREAD_MUTEX_INITIALIZER;  // protegge read_count
pthread_mutex_t rw_mutex = PTHREAD_MUTEX_INITIALIZER;  // accesso esclusivo alla risorsa
int read_count = 0;
int shared_data = 0;

void start_read(void) {
    // TODO:
    // 1. prendere mutex
    // 2. incrementare read_count
    // 3. se sono il primo lettore -> prendere rw_mutex
    // 4. rilasciare mutex
}

void end_read(void) {
    // TODO:
    // 1. prendere mutex
    // 2. decrementare read_count
    // 3. se sono l’ultimo lettore -> rilasciare rw_mutex
    // 4. rilasciare mutex
}

void* reader(void* arg) {
    long id = (long)arg;
    while (1) {
        start_read();
        printf("[R%ld] legge: %d\n", id, shared_data);
        usleep(100000);
        end_read();
        usleep(100000);
    }
    return NULL;
}

void* writer(void* arg) {
    long id = (long)arg;
    while (1) {
        pthread_mutex_lock(&rw_mutex);
        shared_data++;
        printf("   [W%ld] scrive: %d\n", id, shared_data);
        usleep(150000);
        pthread_mutex_unlock(&rw_mutex);
        usleep(200000);
    }
    return NULL;
}

int main(void) {
    const int N_READERS = 3;
    const int N_WRITERS = 2;
    pthread_t r[N_READERS], w[N_WRITERS];

    for (long i = 0; i < N_READERS; i++)
        pthread_create(&r[i], NULL, reader, (void*)i);

    for (long i = 0; i < N_WRITERS; i++)
        pthread_create(&w[i], NULL, writer, (void*)i);

    for (int i = 0; i < N_READERS; i++)
        pthread_join(r[i], NULL);
    for (int i = 0; i < N_WRITERS; i++)
        pthread_join(w[i], NULL);

    return 0;
}
