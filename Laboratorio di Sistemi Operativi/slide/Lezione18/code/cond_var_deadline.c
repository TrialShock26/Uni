// cond_timedwait_example.c
// Esempio di attesa su variabile di condizione con deadline

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond = PTHREAD_COND_INITIALIZER;
int ready = 0;   // evento da attendere

// questo thread simula qualcuno che *forse* segnala dopo un po'
void* worker(void* arg) {
    // prova a cambiare questo tempo per vedere timeout / no timeout
    sleep(3);   // se metti 1, il main NON fa timeout
    pthread_mutex_lock(&mtx);
    ready = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mtx);
    return NULL;
}

int main(void) {
    pthread_t th;
    pthread_create(&th, NULL, worker, NULL);

    pthread_mutex_lock(&mtx);

    // calcolo la deadline: ora + 2 secondi
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += 2;   // deadline tra 2 secondi

    int rc = 0;
    while (!ready && rc == 0) {
        rc = pthread_cond_timedwait(&cond, &mtx, &ts);
        // ritorna 0 se qualcuno ha fatto signal/broadcast
        // ritorna ETIMEDOUT se è scaduta la deadline
    }

    if (ready) {
        printf("Evento arrivato prima della deadline ✅\n");
    } else if (rc == ETIMEDOUT) {
        printf("Timeout scaduto ⏰, vado avanti lo stesso\n");
    } else {
        printf("Errore su pthread_cond_timedwait: %d\n", rc);
    }

    pthread_mutex_unlock(&mtx);

    pthread_join(th, NULL);
    return 0;
}
