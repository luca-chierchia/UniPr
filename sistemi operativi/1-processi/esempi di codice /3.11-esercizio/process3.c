#include <stdio.h>
#include <unistd.h>

// Compreso il processo padre iniziale, quanti processi vengono  creati dal programma mostrato

int main()
{
  int i;
  for (i = 0; i < 4; i++)
    fork(); // vengono creati in totale 2^4 = 16 processi totali incluso il padre
  return 0;
}
