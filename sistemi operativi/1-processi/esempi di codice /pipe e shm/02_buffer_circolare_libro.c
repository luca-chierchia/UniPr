/*
 * Figure 3.12 e 3.13 (+ dichiarazioni del Paragrafo 3.5.1)
 * Produttore e consumatore con buffer limitato in memoria condivisa,
 * attesa attiva (busy waiting).
 *
 * Il libro mostra solo i due cicli: qui sono completati con il minimo
 * indispensabile per poterli eseguire. Le parti NON presenti nel libro sono
 * marcate [SCAFFOLDING]:
 *   - la regione di memoria condivisa (mmap anonima) e la fork()
 *   - un numero finito di elementi (nel libro i cicli sono infiniti)
 *
 * Compilazione:  gcc -Wall -O0 -o 02_buffer_libro 02_buffer_circolare_libro.c
 * ATTENZIONE: con -O2 il consumatore puo' restare bloccato per sempre
 *             (vedi i problemi descritti nel commento sul consumatore).
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define BUFFER_SIZE 10
#define N_ELEMENTI  25                 /* [SCAFFOLDING] */

// struct generica che contiene una variabile di tipo int, ma potrebbe
// qualsiasi altra informazione come ad esempio stringhe o strutture
// dati più complesse

/*
  typedef struct {
  int id;
  int priorita;
  int dimensione;
  } elemento;
*/

typedef struct {
  int valore;
} elemento;   /* il libro: struct { . . . } elemento */

/* Nel libro sono variabili "in memoria condivisa": buffer, in, out */
typedef struct {                       /* [SCAFFOLDING] */
  elemento buffer[BUFFER_SIZE];
  int in;     /* prossima posizione libera */
  int out;    /* prima posizione piena     */
} condiviso_t;

static void produttore(condiviso_t *c)
{
  elemento next_produced;
  int prodotti = 0;
  while (prodotti < N_ELEMENTI) {            /* libro: while (true) */
    /* produce un elemento in next_produced */
    next_produced.valore = prodotti * 10;

    /* buffer pieno quando (in+1)%BUFFER_SIZE == out: attesa attiva,
       il processo consuma CPU ripetendo il test */
    while (((c->in + 1) % BUFFER_SIZE) == c->out)
      ;                                  /* non fa niente */

    c->buffer[c->in] = next_produced;
    c->in = (c->in + 1) % BUFFER_SIZE;
    prodotti++;
  }
}

static void consumatore(condiviso_t *c)
{
  elemento next_consumed;
  int consumati = 0;
  while (consumati < N_ELEMENTI) {           /* libro: while (true) */
    /* buffer vuoto quando in == out: attesa attiva.
       PROBLEMA: c->in non e' volatile/atomico, quindi il compilatore
       (con -O2) puo' leggerlo una volta sola e non vedere mai gli
       aggiornamenti fatti dall'altro processo. */
    while (c->in == c->out)
      ;                                  /* non fa niente */

    next_consumed = c->buffer[c->out];
    c->out = (c->out + 1) % BUFFER_SIZE;

    /* consuma l'elemento in next_consumed */
    printf("consumato: %d\n", next_consumed.valore);
    consumati++;
  }
}

int main(void)
{
  /* [SCAFFOLDING] regione condivisa tra padre e figlio */
  // mmap() permette di creare una mappatura in memoria virtuale, in
  // questo caso viene utilizzata per ottenere una regione di memoria
  // condivisibile tra i due processi.
  /*
    | Parametro | Significato |
    |---|---|
    | `NULL` | Il sistema operativo sceglie l'indirizzo virtuale iniziale. |
    | `sizeof *c` | Dimensione della regione da mappare.(dimensione
    |del buffer |
    | `PROT_READ` | Permette la lettura. |
    | `PROT_WRITE` | Permette la scrittura. |
    | `MAP_SHARED` | Le modifiche sono visibili agli altri processi
    |che condividono  la mappatura. |
    | `MAP_ANONYMOUS` | La memoria non è associata a un file. |
    | `-1` | File descriptor non utilizzato. |
    | `0` | Offset iniziale della mappatura. |

  */
  condiviso_t *c = mmap(NULL, sizeof *c, PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if (c == MAP_FAILED){
    perror("mmap");
    return 1;
  }
  c->in = 0;                  /* int in = 0;  */
  c->out = 0;                 /* int out = 0; */

  pid_t pid = fork();
  if (pid < 0) { perror("fork"); return 1; }
  if (pid == 0) {
    consumatore(c);
    exit(0); }   /* exit(), non _exit(): svuota stdout */

  produttore(c);
  wait(NULL);
  return 0;
}
