#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#include "err.h"


/*Liczba dzieci*/
#define N   15
#define K   5

#define SIGTOWAIT (SIGRTMIN + 1)

int k = 0;

void waitToEnd(sigset_t block_mask) {
    k++;
    if (k == K) {
        if (sigprocmask(SIG_UNBLOCK, &block_mask, 0) == -1)
            syserr("sigprocmask unblock");
    }
}

int main() {

    pid_t parent_pid, child_pid[N];
    int i = 0;
    srand((unsigned) time(0));  // losowość

    parent_pid = getpid();

    sigset_t block_mask;
    sigemptyset(&block_mask);

    sigaddset(&block_mask, SIGTOWAIT);
    if (sigprocmask(SIG_BLOCK, &block_mask, 0) == -1)
        syserr("sigprocmask block");

    struct sigaction action;
    action.sa_handler = (__sighandler_t) waitToEnd;
    action.sa_mask = block_mask;
    action.sa_flags = 0;

    if (sigaction(SIGTOWAIT, &action, 0) == -1)
        syserr("kill");

    for (i = 0; i < N; ++i) {    //tworzę N dzieci
        int sleep_time = rand() % 10 + 1;   // pseudolosowość wymaga losowania w rodzicu
        switch (child_pid[i] = fork()) {

            case -1:
                syserr("Error in fork\n");
            case 0:
                /*child*/
                printf("Dziecko %d: Zaczynam\n\n", getpid());
                sleep(sleep_time);  // wymagana drzemka

                if (kill(child_pid[i], SIGTOWAIT) == -1)
                    syserr("kill");

                printf("Dziecko %d: Kończę\n\n", getpid());
                return 0;
            default:
#ifdef D
                printf("Parent %d\n", i);
#endif
                break;
        }
    }
    /*parent*/

    i = 0;
    while (i < N) {
        printf("Czekam na dziecko\n");
        if (wait(0) == -1) {
            syserr("wait");
        } else {
            printf("Odebrałem dziecko\n");
            ++i;
        }
    }

    printf("Rodzic: Kończę\n");

    return 0;
}
/**********************************************************************/