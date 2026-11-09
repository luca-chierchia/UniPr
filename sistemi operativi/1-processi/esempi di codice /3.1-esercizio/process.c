#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int value = 5;

int main()
{
  pid_t pid; // potrebbe andare bene anche un tipo int, ma può variare in base al sistema
  pid = fork(); // restituisce due valori di ritorno, il PID > 0 del figlio al padre, ed al figlio 0
  // il valore di ritorno 0 al figlio non è il suo pid, 0 indica che il processo figlio è stata creato correttamente

  if (pid == 0) { /* processo figlio */
    value += 15; // la variabile value del processo figlio assume valore 20
    pid_t pid_f;
    pid_f = getpid();
    printf("pid processo figlio: %d\nvalue figlio: %d\n",pid_f,value);
    return 0; // qui termina il processo figlio
  }
  else if (pid > 0) { /* processo padre */
    wait(NULL); // attendiamo che il processo figlio sia terminato
    pid_t pid_p = getpid();
    printf("il processo padre ha pid: %d\nvalue padre: %d\n",pid_p,value );
    return 0; // qui termina il processo padre
  }
}
