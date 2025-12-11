#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int stato = 1;  // 1 = tocca a t1, 2 = t2, 3 = t3

void* thread1(void* arg) {
    //TODO: mutex

    while (stato != 1) {
        pthread_cond_wait(&cond, &mtx);
    }

    printf("t1 inizia\n");

    printf("t1 finisce -> sveglia t2\n");

    // TODO: aggiornare stato in modo che tocchi a t2

    //TODO: mutex
    return NULL;
}

void* thread2(void* arg) {
    //TODO: mutex

    // TODO: aspettare finché stato non indica che è il turno di t2

    printf("t2 inizia\n");
    // TODO: eventuale "lavoro"

    printf("t2 finisce -> sveglia t3\n");

    // TODO: aggiornare stato per far partire t3
    // TODO: svegliare gli altri thread

    //TODO: mutex
    return NULL;
}

void* thread3(void* arg) {
    //TODO: mutex

    // TODO: aspettare finché stato non indica che è il turno di t3

    printf("t3 inizia\n");
    // TODO: eventuale "lavoro"

    printf("t3 finisce\n");

    //TODO: mutex
    return NULL;
}

int main(void) {
    pthread_t t1, t2, t3;

    // TODO: creare i 3 thread
    // pthread_create(&t1, ...)

    // TODO: fare la join dei 3 thread

    // TODO: distruggere mutex e condition

    return 0;
}
