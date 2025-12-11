#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>    
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  c = PTHREAD_COND_INITIALIZER;

int ready = 0;

void* worker(void* arg) {
    pthread_mutex_lock(&m);
    while (!ready)
        pthread_cond_wait(&c, &m);
    printf("OK\n");
    pthread_mutex_unlock(&m);
    return NULL;
}

int main(void) {
    pthread_t t;
    pthread_create(&t, NULL, worker, NULL);
    pthread_mutex_lock(&m);
    // simuliamo un po' di lavoro
    sleep(2);
    pthread_mutex_lock(&m);
    
    ready = 1;
    pthread_cond_signal(&c);

    pthread_join(t, NULL);
    return 0;
}

