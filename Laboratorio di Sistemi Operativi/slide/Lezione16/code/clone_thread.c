#define _GNU_SOURCE
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define STACK_SIZE (1024 * 1024)
static char child_stack[STACK_SIZE];

int global = 0;

int thread_fn(void *arg) {
    printf("[thread] PID = %d, global = %d\n", getpid(), global);
    global = 42;
    printf("[thread] modifico global = %d\n", global);
    return 0;
}

int main(void) {
    printf("[main] PID = %d, global = %d\n", getpid(), global);

    /* CLONE_VM → memoria condivisa ⇒ comportamento da thread */
    pid_t pid = clone(thread_fn,
                      child_stack + STACK_SIZE,
                      CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | SIGCHLD,
                      NULL);

    if (pid == -1) {
        perror("clone");
        exit(1);
    }

    sleep(1);
    printf("[main] dopo clone: global = %d (memoria condivisa)\n", global);
    return 0;
}
