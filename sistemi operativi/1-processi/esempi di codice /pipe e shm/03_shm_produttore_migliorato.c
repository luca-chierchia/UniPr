/*
 * Figura 3.16 - produttore con memoria condivisa POSIX, versione migliorata.
 * Va usato insieme a 03_shm_consumatore_migliorato.c
 *
 * Miglioramenti:
 *   1. nome dell'oggetto "/OS" (forma portabile: inizia con '/')
 *   2. permessi 0600 invece di 0666 (solo il proprietario)
 *   3. controllo di TUTTE le chiamate di sistema
 *   4. snprintf con limite: nessun overflow oltre SIZE
 *   5. si scrive "Hello" "World!" come un'unica stringa terminata da '\0'
 *      (nel libro il puntatore avanzato dopo la seconda sprintf non serve)
 *   6. sincronizzazione con un semaforo con nome: il consumatore parte
 *      solo DOPO che il produttore ha finito di scrivere (nel libro bisogna
 *      ricordarsi di lanciare prima il produttore)
 *   7. munmap() e close() finali
 *
 * Compilazione:  gcc -Wall -Wextra -pthread -o 03_prod_migliorato \
 *                    03_shm_produttore_migliorato.c
 */
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
    const char *message_0 = "Hello";
    const char *message_1 = "World!";

    /* semaforo con nome, valore iniziale 0: "dati non ancora pronti" */
    sem_t *pronto = sem_open(SEM_NAME, O_CREAT, 0600, 0);
    if (pronto == SEM_FAILED) { perror("sem_open"); return EXIT_FAILURE; }

    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0600);
    if (fd == -1) { perror("shm_open"); return EXIT_FAILURE; }

    if (ftruncate(fd, SIZE) == -1) { perror("ftruncate"); return EXIT_FAILURE; }

    char *ptr = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) { perror("mmap"); return EXIT_FAILURE; }

    /* (4)(5) scrittura limitata alla dimensione dell'oggetto */
    int n = snprintf(ptr, SIZE, "%s%s", message_0, message_1);
    if (n < 0 || n >= SIZE) {
        fprintf(stderr, "messaggio troppo lungo\n");
        return EXIT_FAILURE;
    }

    sem_post(pronto);              /* (6) avvisa il consumatore */

    munmap(ptr, SIZE);             /* (7) */
    close(fd);
    sem_close(pronto);
    return EXIT_SUCCESS;
}
