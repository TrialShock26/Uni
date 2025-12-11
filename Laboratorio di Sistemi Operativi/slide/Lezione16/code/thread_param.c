#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* --- struct per il terzo esempio --- */
typedef struct {
    int start;
    int end;
} thread_args;

/* --- 1) Passo una stringa e la converto --- */
void *runner_string(void *param) {
    char *s = (char *)param;   // arriva argv[1]
    int value = atoi(s);       // converto in int
    printf("[runner_string] stringa = \"%s\", intero = %d\n", s, value);
    pthread_exit(NULL);
}

/* --- 2) Passo l'indirizzo di un int --- */
void *runner_pointer(void *param) {
    int *p = (int *)param;     // arriva &upper
    int value = *p;            // dereference
    printf("[runner_pointer] valore = %d\n", value);
    pthread_exit(NULL);
}

/* --- 3) Passo l'indirizzo di una struct --- */
void *runner_struct(void *param) {
    thread_args *args = (thread_args *)param;
    printf("[runner_struct] start = %d, end = %d\n",
           args->start, args->end);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t t1, t2, t3;

    /* valori da passare negli esempi 2 e 3 */
    int upper = 42;
    thread_args args;
    args.start = 10;
    args.end   = 20;

    /* --- 1) passo argv[1] se presente, altrimenti uso "100" --- */
    char *val_string = (argc > 1) ? argv[1] : (char *)"100";

    pthread_create(&t1, NULL, runner_string,  val_string);
    pthread_create(&t2, NULL, runner_pointer, &upper);
    pthread_create(&t3, NULL, runner_struct,  &args);

    /* aspetto che finiscano tutti i thread */
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("main: tutti i thread hanno finito.\n");
    return 0;
}
