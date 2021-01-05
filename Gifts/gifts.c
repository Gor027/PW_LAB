#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

#include "err.h"


//some consts
#define MAX_REINDEERS 7
#define MAX_ELFS 6
#define MAX_GIFTS 5

#define NO_REINDEERS 3
#define NO_ELFS 4
#define NO_GIFTS 5

#define BUFFSIZE 3
#define LOOPS 5

/**************************************************************************************************/
//storage compartment
struct storage {
    int gifts[MAX_GIFTS];
    sem_t empty;
    sem_t full;
    sem_t ochrona;
    int putPos;
    int getPos;
};
/**************************************************************************************************/
//popular names
char *elfs_names[MAX_ELFS] = {"Mirek", "Zuzia", "Gienia", "Macius", "Ela", "Stasia"};
char *reindeers_names[MAX_REINDEERS] = {"Janek", "Zosia", "Franek", "Jozek", "Asia", "Olek", "Ruda"};
char *gifts[MAX_GIFTS] = {"lalka", "klocki", "ciuchcia", "rozga", "rower"};

/**************************************************************************************************/
//toymaker
int produce() {
    sleep(rand() % 3);
    return rand() % NO_GIFTS;
}

//sent to santa
void deliver(int i) {
    sleep(rand() % 3);
}

void nap(int i) {
    sleep(i);
}
/**************************************************************************************************/
//life of an elf
void elf(int id, struct storage *s) {

    int i, g;
    printf("Hej! Jestem elfem o imieniu %s, zaczynam!\n", elfs_names[id]);
    for (i = 0; i < LOOPS; ++i) {

        g = produce();
        printf("Hej! Jestem elfem o imieniu %s, wyprodukowalem/am prezent: %s\n", elfs_names[id], gifts[g]);

        // P on empty
        if (sem_wait(&s->empty))
            syserr("child sem_wait");

        // P on ochrona
        if (sem_wait(&s->ochrona))
            syserr("child ochrona");

        s->gifts[s->putPos] = g;
        s->putPos = (s->putPos + 1) % BUFFSIZE;

        printf("Hej! Jestem elfem o imieniu %s, wstawilem/am prezent: %s\n", elfs_names[id], gifts[g]);

        if (sem_post(&s->ochrona))
            syserr("sem_post");

        if (sem_post(&s->full))
            syserr("sem_post");
    }
}

/**************************************************************************************************/
//life of a reindeer
void reindeer(int id, struct storage *s) {

    int end = 0;
    int g;

    printf("Hej! Jestem reniferem o imieniu %s, zaczynam!\n", reindeers_names[id]);
    while (!end) {
        // P on full
        if (sem_wait(&s->full))
            syserr("child sem_wait");

        // P on ochrona
        if (sem_wait(&s->ochrona))
            syserr("child ochrona");

        g = s->gifts[s->getPos];
        s->getPos = (s->getPos + 1) % BUFFSIZE;
        printf("Hej! Jestem reniferem o imieniu %s, odebralem/am prezent: %s\n", reindeers_names[id], gifts[g]);

        // It can be after sem_post...
        deliver(g);
        printf("Hej! Jestem reniferem o imieniu %s dostarczylem/am prezent: %s\n", reindeers_names[id], gifts[g]);

        if (sem_post(&s->ochrona))
            syserr("sem_post");

        if (sem_post(&s->empty))
            syserr("sem_post");
    }
}
/**************************************************************************************************/
/**************************************************************************************************/

void init_storage(struct storage *mag) {
    mag = malloc(sizeof(struct storage));
    mag->putPos = 0;
    mag->getPos = 0;

    if (sem_init(&mag->ochrona, 1, 1))
        syserr("sem_init");

    if (sem_init(&mag->empty, 1, BUFFSIZE))
        syserr("sem_init");

    if (sem_init(&mag->full, 1, 0))
        syserr("sem_init");
}

void destroy(struct storage *mag) {
    if (sem_destroy(&mag->empty))
        syserr("sem_destroy");
    if (sem_destroy(&mag->full))
        syserr("sem_destroy");
    if (sem_destroy(&mag->ochrona))
        syserr("sem_destroy");

    free(mag);
}

int main() {

    int i;
    pid_t pid;

    struct storage *magazyn = NULL;
    init_storage(magazyn);

    struct storage *mapped_mem;

    int fd_memory = -1;
    int flags, prot;

    prot = PROT_READ | PROT_WRITE;
    flags = MAP_SHARED | MAP_ANONYMOUS;

    mapped_mem = (struct storage *) mmap(NULL, sizeof(struct storage), prot, flags,
                                         fd_memory, 0);


    if (mapped_mem == MAP_FAILED)
        syserr("mmap");

    int seed = time(0);
    srand(seed);

    printf("Tworze pracownikow.\nElfy: %d; Renifery: %d\n", NO_ELFS, NO_REINDEERS);

    for (i = 0; i < NO_ELFS + NO_REINDEERS; i++) {

        rand();//some randomness
        switch (pid = fork()) {
            case -1:
                syserr("fork");
            case 0:
                srand(rand());
                if (i < NO_ELFS) {
                    printf("Elf %d!\n", i);
                    elf(i, mapped_mem);

                } else {
                    printf("Renifer %d!\n", i);
                    reindeer(i - NO_ELFS, mapped_mem);
                }
                return 0;
            default:
                nap(1);
                printf("Kolejny pracownik!\n");
                break;
        }
    }

    for (i = 0; i < NO_ELFS + NO_REINDEERS; ++i) wait(0);
    // Destroy storage
    destroy(magazyn);

    // Ending work with shared memory...
    munmap(mapped_mem, sizeof(struct storage));

    return 0;
}
