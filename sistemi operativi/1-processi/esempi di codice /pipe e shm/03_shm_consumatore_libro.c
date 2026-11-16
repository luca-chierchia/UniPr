/*
 * Figura 3.17 - Consumatore con memoria condivisa POSIX.
 *
 * Correzioni minime rispetto al testo del libro (errori di stampa):
 *   - <stlib.h>          ->  <stdlib.h>
 *   - const int SIZE 4096;  ->  const int SIZE = 4096;
 *
 * ATTENZIONE: il codice del libro apre l'oggetto in sola lettura
 * (O_RDONLY) ma lo mappa con PROT_READ | PROT_WRITE e MAP_SHARED. Su Linux
 * questa combinazione e' rifiutata da mmap() (errore EACCES): ptr vale
 * MAP_FAILED e la printf() successiva causa un segmentation fault.
 * Il codice e' lasciato come nel libro; la correzione e' nel file
 * migliorato (PROT_READ).
 *
 * Compilazione:  gcc -Wall -o 03_cons_libro 03_shm_consumatore_libro.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main()
{
    /* dimensione, in byte, dell'oggetto memoria condivisa */
    const int SIZE = 4096;
    /* nome dell'oggetto memoria condivisa */
    const char *name = "OS";
    /* descrittore del file di memoria condivisa */
    int fd;
    /* puntatore all'oggetto memoria condivisa */
    void *ptr;

    /* apre l'oggetto memoria condivisa: fallisce (fd = -1) se il produttore
       non e' ancora stato eseguito, ma il risultato non e' controllato */
    fd = shm_open(name, O_RDONLY, 0666);

    /* mappa in memoria l'oggetto (vedi avvertenza in testa al file) */
    ptr = (char *)
        mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    /* legge dall'oggetto memoria condivisa: stampa fino al primo '\0' */
    printf("%s", (char *)ptr);

    /* rimuove l'oggetto memoria condivisa */
    shm_unlink(name);

    return 0;
}
