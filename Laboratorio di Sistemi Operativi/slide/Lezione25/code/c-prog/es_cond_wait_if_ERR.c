// correggi l'errore di questo codice
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  c = PTHREAD_COND_INITIALIZER;

int ready = 0;

void* worker(void* arg) {
    int id = (int)(long)arg;

    pthread_mutex_lock(&m);
 
    if (!ready)
        pthread_cond_wait(&c, &m);

    printf("Thread %d entra nella sezione critica\n", id);
    // questo thread "consuma" la condizione e la rimette a 0
    ready = 0;

    pthread_mutex_unlock(&m);
    return NULL;
}

int main(void) {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, worker, (void*)1);
    pthread_create(&t2, NULL, worker, (void*)2);

    sleep(1);  // do il tempo ai thread di mettersi in wait

    pthread_mutex_lock(&m);
    ready = 1;
    // sveglio TUTTI i thread che aspettano
    pthread_cond_broadcast(&c);
    pthread_mutex_unlock(&m);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
