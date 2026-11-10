#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

// In quali circostanze la linea di codice contrassegnata printf("LINE J"); verrà raggiunta

int main()
{
  pid_t pid;
  /* crea un processo figlio */
  pid = fork();
  if (pid < 0) { /* si è verificato un errore */
    fprintf(stderr, "Fork Failed");
    return 1;
  }
  else if (pid == 0) { /* processo figlio */
    execlp("/bin/ls","ls",NULL);
    // la funzione execlp() fa parte delle funzione della famiglia exec()
    // in questo caso si sta dicendo al processo figlio di caricare un altro programma
    // il programma ls dalla cartella /bin/ls, di conseguenza avendo caricato un altro programma
    // non raggiungerà la printf
    // la printf("LINE J"); viene raggiunta se il programma non viene caricato.
    printf("LINE J\n");
  }
  else { /* processo padre*/
    /* il padre attende che il figlio termini */
    wait(NULL);
    printf("Child Complete");
  }
  return 0;
}
