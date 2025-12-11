#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* funzione di avvio del thread */
void *tbody(void *arg)
{
    int *pi = (int *)arg;    /* arg è quello che gli abbiamo passato nel create */
    printf("Ciao, sono il thread: mi hanno appena creato\n");

    *pi = 10;                /* scrivo nel dato del main tramite il puntatore */

    sleep(2);                /* faccio finta di lavorare */

    /* preparo un valore di ritorno */
    int *ret = malloc(sizeof(int));
    *ret = 50;

    /* termino il thread restituendo un puntatore a int */
    pthread_exit((void *)ret);
    /* (equivalente) return (void *)ret; */
}

int main(int argc, char **argv)
{
    pthread_t mythread;
    int i = 0;
    void *result;            /* qui arriverà il valore di ritorno del thread */

    printf("Sono il main: ora creo un thread\n");

    /* passo l'indirizzo di i al thread */
    pthread_create(&mythread, NULL, tbody, (void *)&i);

    printf("Main: ora aspetto che il thread termini\n");

    /* &result perché pthread_join scrive dentro result */
    pthread_join(mythread, &result);

    printf("Main: il thread ha assegnato %d a i\n", i);

    /* result è un void*, lo casto a int* per leggerlo */
    printf("Main: il thread ha restituito %d\n", *(int *)result);

    /* libero la memoria allocata dal thread */
    free(result);

    return 0;
}
