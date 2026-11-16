/*
 * Figura 3.16 - Produttore con memoria condivisa POSIX.
 *
 * Correzioni minime rispetto al testo del libro (errori di stampa che
 * impediscono la compilazione):
 *   - <stlib.h>          ->  <stdlib.h>
 *   - const int SIZE 4096;  ->  const int SIZE = 4096;
 *   - aggiunto #include <unistd.h>, necessario per ftruncate() (il libro non
 *     lo include: la funzione resta "implicita")
 *
 * Compilazione:  gcc -Wall -o 03_prod_libro 03_shm_produttore_libro.c
 *                (su glibc < 2.34 aggiungere -lrt)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>      /* [AGGIUNTO] per ftruncate() */
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
    /* stringhe scritte nella memoria condivisa */
    const char *message_0 = "Hello";
    const char *message_1 = "World!";
    /* descrittore del file di memoria condivisa */
    int fd;
    /* puntatore all'oggetto memoria condivisa */
    char *ptr;

    /* crea l'oggetto memoria condivisa (permessi 0666: leggibile e
       scrivibile da chiunque) */
    fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    /* configura la dimensione dell'oggetto: senza questa chiamata l'oggetto
       ha lunghezza 0 e ogni accesso causerebbe SIGBUS */
    ftruncate(fd, SIZE);

    /* mappa in memoria l'oggetto */
    ptr = (char *)
        mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    /* scrive sull'oggetto memoria condivisa */
    sprintf(ptr, "%s", message_0);   /* scrive "Hello" + '\0'          */
    ptr += strlen(message_0);        /* si porta sul '\0' appena scritto */
    sprintf(ptr, "%s", message_1);   /* lo sovrascrive: "HelloWorld!"   */
    ptr += strlen(message_1);        /* (incremento inutile: mai usato) */

    return 0;   /* nessun munmap/close: lo fa il kernel all'uscita.
                   L'oggetto "OS" resta pero' nel sistema finche' qualcuno
                   non chiama shm_unlink(). */
}
