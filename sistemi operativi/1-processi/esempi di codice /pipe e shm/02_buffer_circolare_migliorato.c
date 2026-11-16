/*
 * Figure 3.12 e 3.13 - versione migliorata.
 *
 * Miglioramenti:
 *   1. niente attesa attiva: due semafori POSIX condivisi tra processi
 *      (sem_init con pshared = 1) fanno dormire chi deve aspettare
 *        - "vuoti": posti liberi, inizialmente BUFFER_SIZE
 *        - "pieni": elementi disponibili, inizialmente 0
 *   2. i semafori garantiscono anche la visibilita' in memoria delle scritture
 *      (niente piu' problemi con l'ottimizzazione del compilatore)
 *   3. si usano TUTTI i BUFFER_SIZE posti (il libro ne sfrutta BUFFER_SIZE-1)
 *   4. 'in' e 'out' sono locali: ognuno e' scritto da un solo processo
 *   5. controllo degli errori, wait del figlio, munmap/sem_destroy finali
 *
 * Limite rimasto: va bene per UN produttore e UN consumatore. Con piu'
 * produttori (o consumatori) serve anche un mutex per proteggere in/out.
 *
 * Compilazione:  gcc -Wall -Wextra -O2 -pthread -o 02_buffer_migliorato \
 *                    02_buffer_circolare_migliorato.c
 */
#include <errno.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define BUFFER_SIZE 10
#define N_ELEMENTI  25

typedef struct { int valore; } elemento;

typedef struct {
    elemento buffer[BUFFER_SIZE];
    sem_t vuoti;     /* posti liberi            */
    sem_t pieni;     /* elementi da consumare   */
} condiviso_t;

/* sem_wait puo' essere interrotta da un segnale: si riprova */
static void attendi(sem_t *s)
{
    while (sem_wait(s) == -1 && errno == EINTR)
        ;
}

static void produttore(condiviso_t *c)
{
    int in = 0;
    for (int n = 0; n < N_ELEMENTI; n++) {
        elemento next_produced = { n * 10 };
        attendi(&c->vuoti);                    /* dorme se il buffer e' pieno */
        c->buffer[in] = next_produced;
        in = (in + 1) % BUFFER_SIZE;
        sem_post(&c->pieni);                   /* sveglia il consumatore */
    }
}

static void consumatore(condiviso_t *c)
{
    int out = 0;
    for (int n = 0; n < N_ELEMENTI; n++) {
        attendi(&c->pieni);                    /* dorme se il buffer e' vuoto */
        elemento next_consumed = c->buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&c->vuoti);                   /* un posto in piu' per il produttore */
        printf("consumato: %d\n", next_consumed.valore);
    }
}

int main(void)
{
    condiviso_t *c = mmap(NULL, sizeof *c, PROT_READ | PROT_WRITE,
                          MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (c == MAP_FAILED) { perror("mmap"); return EXIT_FAILURE; }

    if (sem_init(&c->vuoti, 1, BUFFER_SIZE) == -1 ||   /* 1 = condiviso tra processi */
        sem_init(&c->pieni, 1, 0) == -1) {
        perror("sem_init");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return EXIT_FAILURE; }
    if (pid == 0) { consumatore(c); exit(EXIT_SUCCESS); }

    produttore(c);

    int status;
    waitpid(pid, &status, 0);

    sem_destroy(&c->vuoti);
    sem_destroy(&c->pieni);
    munmap(c, sizeof *c);
    return (WIFEXITED(status) && WEXITSTATUS(status) == 0)
           ? EXIT_SUCCESS : EXIT_FAILURE;
}
