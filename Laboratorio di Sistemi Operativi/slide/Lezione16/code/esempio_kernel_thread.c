#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>   // per SYS_gettid
#include <stdint.h>

void *worker(void *arg) {
    int id = *(int *)arg;          // argomento numerico portabile
	char c;

    pthread_t self = pthread_self();      // ID POSIX (gestito dalla libreria)
    pid_t tid = syscall(SYS_gettid);      // ID del kernel (TID reale)

    printf("[thread %d] pthread_self() = %lu, gettid() = %d, PID (TGID) = %d\n",
           id, (unsigned long)self, tid, getpid());

    /* blocco per osservare i thread con ps */
    read(STDIN_FILENO, &c, 1);

    return NULL;
}

int main(void) {
    pthread_t t1, t2;
	int id1 = 1, id2 = 2;

    printf("[main] PID (Thread Group ID) = %d\n", getpid());

    pthread_create(&t1, NULL, worker, (void *)&id1);
    pthread_create(&t2, NULL, worker, (void *)&id2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
