#include <stdio.h>
#include <pthread.h>

#define NUM_TURNI 5

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  c = PTHREAD_COND_INITIALIZER;

int turn = 0;   // 0 = tocca ad A, 1 = tocca a B

void* threadA(void* arg) {
    for (int i = 0; i < NUM_TURNI; i++) {
        // TODO: prendere il mutex
        // TODO: aspettare che turn valga 0
        printf("A\n");
        // TODO: passare il turno a B
        // TODO: rilasciare il mutex
    }
    return NULL;
}

void* threadB(void* arg) {
    for (int i = 0; i < NUM_TURNI; i++) {
        // TODO: prendere il mutex
        // TODO: aspettare che turn valga 1
        printf("B\n");
        // TODO: passare il turno ad A
        // TODO: rilasciare il mutex
    }
    return NULL;
}

int main(void) {
    pthread_t tA, tB;

    pthread_create(&tA, NULL, threadA, NULL);
    pthread_create(&tB, NULL, threadB, NULL);

    pthread_join(tA, NULL);
    pthread_join(tB, NULL);

    return 0;
}
