/*
 * Figura 3.17 - consumatore con memoria condivisa POSIX, versione migliorata.
 *
 * Miglioramenti:
 *   1. correzione dell'errore del libro: oggetto aperto O_RDONLY => la
 *      mappatura deve essere solo PROT_READ (con PROT_WRITE + MAP_SHARED
 *      mmap() fallisce e il programma andava in segmentation fault)
 *   2. attesa del semaforo: si legge solo dopo che il produttore ha scritto
 *   3. controllo di tutte le chiamate di sistema
 *   4. stampa limitata a SIZE byte ("%.*s"), anche se manca il '\0'
 *   5. pulizia completa: munmap, close, shm_unlink e sem_unlink
 *
 * Compilazione:  gcc -Wall -Wextra -pthread -o 03_cons_migliorato \
 *                    03_shm_consumatore_migliorato.c
 */
#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define SHM_NAME "/OS"
#define SEM_NAME "/OS_pronto"
#define SIZE     4096

int main(void)
{
    /* O_CREAT con lo stesso valore iniziale del produttore: non importa
       chi dei due parte per primo */
    sem_t *pronto = sem_open(SEM_NAME, O_CREAT, 0600, 0);
    if (pronto == SEM_FAILED) { perror("sem_open"); return EXIT_FAILURE; }

    /* (2) si blocca finche' il produttore non ha finito di scrivere */
    while (sem_wait(pronto) == -1 && errno == EINTR)
        ;

    int fd = shm_open(SHM_NAME, O_RDONLY, 0);
    if (fd == -1) { perror("shm_open"); return EXIT_FAILURE; }

    /* (1) sola lettura: PROT_READ */
    const char *ptr = mmap(NULL, SIZE, PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) { perror("mmap"); return EXIT_FAILURE; }

    printf("%.*s\n", SIZE, ptr);           /* (4) lettura limitata */

    /* (5) pulizia */
    munmap((void *)ptr, SIZE);
    close(fd);
    shm_unlink(SHM_NAME);
    sem_close(pronto);
    sem_unlink(SEM_NAME);
    return EXIT_SUCCESS;
}
