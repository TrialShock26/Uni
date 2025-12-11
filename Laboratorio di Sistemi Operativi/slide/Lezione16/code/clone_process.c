#define _GNU_SOURCE
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define STACK_SIZE (1024 * 1024)
static char child_stack[STACK_SIZE];

int global = 0;

int child_fn(void *arg) {
    printf("[clone-fork] PID = %d, global = %d\n", getpid(), global);
    global = 99;
    printf("[clone-fork] modifico global = %d\n", global);
    return 0;
}

int main(void) {
    printf("[main] PID = %d, global = %d\n", getpid(), global);

    /* Nessun CLONE_VM → memoria NON condivisa ⇒ comportamento da fork */
    pid_t pid = clone(child_fn,
                      child_stack + STACK_SIZE,
                      SIGCHLD,   // solo SIGCHLD → clone "processo"
                      NULL);

    if (pid == -1) {
        perror("clone");
        exit(1);
    }

    sleep(1);
    printf("[main] dopo clone-fork: global = %d (memoria separata)\n", global);
    return 0;
}
