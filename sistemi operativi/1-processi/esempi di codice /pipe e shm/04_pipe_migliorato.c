/*
 * Figure 3.21 e 3.22 - pipe convenzionale, versione migliorata.
 *
 * Miglioramenti:
 *   1. write_all(): ripete write() finche' tutti i byte sono scritti
 *      (gestisce scritture parziali ed EINTR)
 *   2. il figlio legge IN CICLO fino a EOF (read() == 0), accumulando i
 *      byte: la pipe e' un flusso, non conserva i confini dei messaggi
 *   3. il buffer del figlio e' terminato con '\0' dal programma stesso, in
 *      base ai byte realmente letti (non ci si affida al mittente) e non
 *      puo' mai essere superato
 *   4. controllo degli errori di read(), write(), close()
 *   5. il padre attende il figlio con waitpid() e ne riporta l'esito
 *   6. SIGPIPE ignorato: se il lettore sparisce, write() restituisce
 *      EPIPE e il padre puo' gestire l'errore invece di morire
 *   7. in caso di errore su fork() si chiudono le estremita' aperte
 *   8. messaggi terminati da '\n'
 *
 * Compilazione:  gcc -Wall -Wextra -o 04_pipe_migliorato 04_pipe_migliorato.c
 */
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 25
#define READ_END    0
#define WRITE_END   1

/* scrive tutti i byte richiesti; 0 = ok, -1 = errore */
static int write_all(int fd, const char *buf, size_t len)
{
    while (len > 0) {
        ssize_t n = write(fd, buf, len);
        if (n < 0) {
            if (errno == EINTR) continue;
            return -1;
        }
        buf += n;
        len -= (size_t)n;
    }
    return 0;
}

int main(void)
{
    const char *write_msg = "Greetings";
    char read_msg[BUFFER_SIZE];
    int fd[2];

    signal(SIGPIPE, SIG_IGN);                              /* (6) */

    if (pipe(fd) == -1) { perror("pipe"); return EXIT_FAILURE; }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        close(fd[READ_END]); close(fd[WRITE_END]);         /* (7) */
        return EXIT_FAILURE;
    }

    if (pid > 0) {                                         /* padre */
        close(fd[READ_END]);

        int rc = EXIT_SUCCESS;
        if (write_all(fd[WRITE_END], write_msg, strlen(write_msg)) == -1) {
            perror("write");                               /* (1)(4) */
            rc = EXIT_FAILURE;
        }
        close(fd[WRITE_END]);          /* senza questa il figlio non vedrebbe EOF */

        int status;                                        /* (5) */
        while (waitpid(pid, &status, 0) == -1) {
            if (errno != EINTR) { perror("waitpid"); return EXIT_FAILURE; }
        }
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            fprintf(stderr, "il figlio e' terminato con errore\n");
            rc = EXIT_FAILURE;
        }
        return rc;
    }

    /* figlio */
    close(fd[WRITE_END]);   /* indispensabile: altrimenti EOF non arriverebbe mai */

    size_t tot = 0;
    for (;;) {                                             /* (2) */
        ssize_t n = read(fd[READ_END], read_msg + tot,
                         sizeof read_msg - 1 - tot);       /* (3) riserva 1 byte per '\0' */
        if (n < 0) {
            if (errno == EINTR) continue;
            perror("read");                                /* (4) */
            _exit(EXIT_FAILURE);
        }
        if (n == 0) break;                 /* EOF: il padre ha chiuso la scrittura */
        tot += (size_t)n;
        if (tot == sizeof read_msg - 1) {  /* buffer pieno: messaggio troncato */
            fprintf(stderr, "messaggio troppo lungo, troncato\n");
            break;
        }
    }
    read_msg[tot] = '\0';                                  /* (3) */

    printf("read %s\n", read_msg);                         /* (8) */
    close(fd[READ_END]);
    return EXIT_SUCCESS;
}
