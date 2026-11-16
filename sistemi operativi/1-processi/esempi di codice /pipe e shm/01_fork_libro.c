/*
 * Figura 3.8 (Silberschatz, "Sistemi operativi", 10a ed.)
 * Creazione di un processo con fork() + execlp() + wait().
 *
 * Differenze rispetto al libro (solo per poter compilare):
 *   - aggiunto #include <sys/wait.h> (il libro non lo include: wait() risulta
 *     "implicita", cosa che i compilatori recenti rifiutano)
 *   - virgolette tipografiche sostituite da virgolette ASCII
 *
 * Compilazione:  gcc -Wall -o 01_fork_libro 01_fork_libro.c
 */
#include <sys/types.h>
#include <sys/wait.h>      /* [AGGIUNTO] per wait() */
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    /* genera un nuovo processo: da qui in poi esistono DUE processi
       che eseguono lo stesso codice, con spazi di indirizzi separati */
    pid = fork();

    if (pid < 0) { /* errore: fork() restituisce -1 */
        fprintf(stderr, "generazione del nuovo processo fallita");
        return 1;
    }
    else if (pid == 0) { /* processo figlio: fork() ha restituito 0 */
        /* sostituisce l'immagine del figlio con /bin/ls.
           Se va a buon fine NON ritorna mai. */
        execlp("/bin/ls", "ls", NULL);
        /* <-- se execlp() fallisce, il figlio arriva qui e prosegue
               fino al "return 0" in fondo, senza alcun messaggio */
    }
    else { /* processo genitore: fork() ha restituito il pid del figlio */
        /* il genitore attende il completamento del figlio */
        wait(NULL);
        printf("il processo figlio ha terminato");   /* niente '\n' */
    }
    return 0;
}
