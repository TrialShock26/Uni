/// dining_philosophers_scheletro.c
// Problema della cena dei filosofi (versione monitor simulato con pthread)
// --- Scheletro didattico da completare ---
//
// Obiettivo:
// 1. Implementare pickup(i), putdown(i), test(i)
// 2. Far sì che due filosofi adiacenti non mangino mai insieme
// 3. Usare mutex e condition variables correttamente

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5
#define LEFT(i)  ((i + N - 1) % N)
#define RIGHT(i) ((i + 1) % N)

typedef enum { THINKING, HUNGRY, EATING } state_t;

/* --- Variabili globali --- */
state_t state[N];                   // stato di ciascun filosofo
pthread_mutex_t mtx;                // mutex del monitor
pthread_cond_t self[N];             // condizione associata a ogni filosofo

/* --- Prototipi funzioni del monitor --- */
void pickup(int i);
void putdown(int i);
void test(int i);

/* --- Funzioni da completare --- */

// Controlla se il filosofo i può iniziare a mangiare
void test(int i) {
    // TODO:
    // if il filosofo i è affamato (HUNGRY)
    //     e i suoi vicini non stanno mangiando (EATING)
    // allora:
    //     cambia il suo stato in EATING
    //     e segnala la sua condition variable (pthread_cond_signal)
}

// Prova a prendere le bacchette
void pickup(int i) {
    pthread_mutex_lock(&mtx);

    // TODO:
    // 1. Imposta lo stato di i = HUNGRY
    // 2. Chiama test(i) per verificare se può mangiare
    // 3. Se non può (state[i] != EATING), aspetta sulla sua condizione self[i]
    //    con pthread_cond_wait(&self[i], &mtx);

    pthread_mutex_unlock(&mtx);
}

// Rimette giù le bacchette
void putdown(int i) {
    pthread_mutex_lock(&mtx);

    // TODO:
    // 1. Imposta stato[i] = THINKING
    // 2. Chiama test(LEFT(i)) e test(RIGHT(i)) per vedere se i vicini possono mangiare

    pthread_mutex_unlock(&mtx);
}

/* --- Thread dei filosofi --- */
void* philosopher(void* arg) {
    int i = (int)(long)arg;

    while (1) {
        printf("Filosofo %d sta PENSANDO\n", i);
        usleep(100000 + rand() % 200000);

        pickup(i);

        printf(">>> Filosofo %d sta MANGIANDO\n", i);
        usleep(100000 + rand() % 200000);

        putdown(i);
    }
    return NULL;
}

/* --- MAIN --- */
int main(void) {
    pthread_t th[N];

    pthread_mutex_init(&mtx, NULL);
    for (int i = 0; i < N; i++) {
        state[i] = THINKING;
        pthread_cond_init(&self[i], NULL);
    }

    for (long i = 0; i < N; i++) {
        if (pthread_create(&th[i], NULL, philosopher, (void*)i) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    for (int i = 0; i < N; i++)
        pthread_join(th[i], NULL);

    pthread_mutex_destroy(&mtx);
    for (int i = 0; i < N; i++)
        pthread_cond_destroy(&self[i]);

    return 0;
}
