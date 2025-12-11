// ponte_senso_unico.c
// Esercizio: massimo N auto sul ponte
// Da completare: aggiungere sem_wait e sem_post nei punti corretti

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_AUTO 10
#define MAX_SUL_PONTE 3

sem_t bridge;  // semaforo contatore per il ponte

void* car(void* arg) {
    long id = (long)arg;

    printf("Auto %ld arriva al ponte\n", id);

    // TODO: attendere permesso di entrare (sem_wait)

    printf("Auto %ld entra nel ponte\n", id);
    sleep(1 + rand() % 2);  // attraversamento

    printf("Auto %ld esce dal ponte\n", id);

    // TODO: segnalare uscita (sem_post)

    return NULL;
}

int main(void) {
    pthread_t th[N_AUTO];
    srand(time(NULL));

    // TODO: inizializzare il semaforo bridge con valore MAX_SUL_PONTE
    // (pshared = 0 → tra thread dello stesso processo)

    for (long i = 0; i < N_AUTO; i++)
        pthread_create(&th[i], NULL, car, (void*)i);

    for (int i = 0; i < N_AUTO; i++)
        pthread_join(th[i], NULL);

    // TODO: distruggere il semaforo

    return 0;
}
