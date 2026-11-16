/*
 * Figura 3.8 - versione migliorata.
 *
 * Miglioramenti:
 *   1. #include <sys/wait.h> e <stdlib.h> (dichiarazioni corrette)
 *   2. se execlp() fallisce il figlio lo segnala e termina con _exit(127),
 *      invece di proseguire eseguendo il codice del padre
 *   3. si attende il PROPRIO figlio con waitpid(), riprovando su EINTR
 *   4. si legge lo stato di uscita del figlio (esito, segnale, codice)
 *   5. fork() fallita: messaggio con perror() che spiega il motivo
 *   6. i messaggi terminano con '\n'
 *
 * Compilazione:  gcc -Wall -Wextra -o 01_fork_migliorato 01_fork_migliorato.c
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");                       /* (5) motivo dell'errore */
        return EXIT_FAILURE;
    }

    if (pid == 0) {                           /* figlio */
        execlp("/bin/ls", "ls", (char *)NULL);
        /* (2) si arriva qui SOLO se execlp() e' fallita */
        perror("execlp");
        _exit(127);   /* _exit: non svuota i buffer stdio ereditati dal padre */
    }

    /* padre */
    int status;
    pid_t r;
    do {                                      /* (3) riprova se interrotta */
        r = waitpid(pid, &status, 0);
    } while (r < 0 && errno == EINTR);

    if (r < 0) {
        perror("waitpid");
        return EXIT_FAILURE;
    }

    /* (4) esito del figlio */
    if (WIFEXITED(status))
        printf("il processo figlio ha terminato con codice %d\n",
               WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("il processo figlio e' stato terminato dal segnale %d\n",
               WTERMSIG(status));

    return (WIFEXITED(status) && WEXITSTATUS(status) == 0)
           ? EXIT_SUCCESS : EXIT_FAILURE;
}
