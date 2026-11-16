/*
 * Figure 3.21 e 3.22 - Pipe convenzionale in UNIX tra padre e figlio.
 *
 * Differenze rispetto al libro (solo di forma):
 *   - "#define_BUFFER_SIZE" -> "#define BUFFER_SIZE" (artefatto di stampa)
 *   - virgolette ASCII
 *
 * Compilazione:  gcc -Wall -o 04_pipe_libro 04_pipe_libro.c
 */
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END    0
#define WRITE_END   1

int main(void)
{
    char write_msg[BUFFER_SIZE] = "Greetings";
    char read_msg[BUFFER_SIZE];          /* NON inizializzato */
    int fd[2];
    pid_t pid;

    /* crea la pipe: fd[0] = lettura, fd[1] = scrittura */
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    /* crea tramite fork un processo figlio: eredita fd[0] e fd[1] */
    pid = fork();

    if (pid < 0) { /* errore */
        fprintf(stderr, "Fork Failed");
        return 1;
    }

    if (pid > 0) { /* processo padre */
        /* chiude l'estremita' inutilizzata della pipe */
        close(fd[READ_END]);

        /* scrive sulla pipe 10 byte ("Greetings" + '\0'); il valore
           restituito da write() non e' controllato */
        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);

        /* chiude l'estremita' di scrittura: il lettore vedra' EOF */
        close(fd[WRITE_END]);
        /* il padre NON chiama wait(): puo' terminare prima del figlio */
    }
    else { /* processo figlio */
        /* chiude l'estremita' inutilizzata della pipe */
        close(fd[WRITE_END]);

        /* legge dalla pipe: una sola read(), bloccante finche' arrivano
           dati; il valore restituito non e' controllato */
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        printf("read %s", read_msg);     /* niente '\n' */

        /* chiude l'estremita' di lettura */
        close(fd[READ_END]);
    }
    return 0;
}
