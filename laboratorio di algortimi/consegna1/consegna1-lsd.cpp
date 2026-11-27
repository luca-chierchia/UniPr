#include <fstream>
#include <limits.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;

// compilazione: g++ consegna1-loader.cpp
// i file di verifica sono stati reinderizzati in output con i comandi
// ./a.out > verifica_ordinamento.txt
// ./a.out > verifica.txt
// ./a.out > consegna1-lsd.txt
//

// Il programma carica il file data.csv contenente 100 righe con dati da ordinare in modo crescente
// ./a.out
// In output viene mostrato il numero di accessi in read alla memoria per eseguire il sorting di ciascuna riga

// Obiettivo:
// Creare un algoritmo di sorting che minimizzi la somma del numero di accessi per ogni sorting di ciascuna riga del file

int ct_swap = 0;
int ct_cmp = 0;
int ct_read = 0;

int max_dim = 0;
int ntests = 100;
int ndiv = 1;
int details = 0;
int graph = 0;

int n = 0; /// dimensione dell'array

void print_array(int *A, int dim) {
    for (int j = 0; j < dim; j++) {
        printf("%d ", A[j]);
    }
    printf("\n");
}

// Radix Sort LSD in base 256, per valori in [-32768, 32767].
void radix_sort(int *A, int *B, int n) {
    const int OFF = 32768;
    int c0[256], c1[256];
    for (int k = 0; k < 256; k++) c0[k] = c1[k] = 0;

    for (int i = 0; i < n; i++) {
        int x = A[i]; ct_read++;
        if (x < -32768 || x > 32767) {
            cerr << "Valore fuori intervallo Radix Sort" << endl;
            exit(1);
        }
        int u = x + OFF;
        c0[u & 255]++; ct_read++;
        c1[u >> 8]++; ct_read++;
    }
    int s0 = 0, s1 = 0;
    for (int k = 0; k < 256; k++) {
        int t0 = c0[k]; ct_read++; c0[k] = s0; s0 += t0;
        int t1 = c1[k]; ct_read++; c1[k] = s1; s1 += t1;
    }
    for (int i = 0; i < n; i++) {
        int x = A[i]; ct_read++;
        int pos = c0[(x + OFF) & 255]++; ct_read++;
        B[pos] = x;
    }
    for (int i = 0; i < n; i++) {
        int x = B[i]; ct_read++;
        int pos = c1[(x + OFF) >> 8]++; ct_read++;
        A[pos] = x;
    }
}

int parse_cmd(int argc, char **argv) {

    /// parsing argomento
    max_dim = 1000;

    for (int i = 1; i < argc; i++) {
        if (argv[i][1] == 'd')
            ndiv = atoi(argv[i] + 3);
        if (argv[i][1] == 't')
            ntests = atoi(argv[i] + 3);
        if (argv[i][1] == 'v')
            details = 1;
        if (argv[i][1] == 'g') {
            graph = 1;
            ndiv = 1;
            ntests = 1;
        }
    }

    return 0;
}

bool isSorted(const int *A, int n) {
    for (int i = 1; i < n; i++) {
        if (A[i - 1] > A[i])
            return false;
    }

    return true;
}

int main(int argc, char **argv) {
    int i, test;
    int *A;
    int *B; /// buffer ausiliario per Radix Sort

    if (parse_cmd(argc, argv))
        return 1;

    /// allocazione array
    A = new int[max_dim];
    B = new int[max_dim];

    n = max_dim;

    // //creazione file input: NON USARE PIU' --> il file data.csv ufficiale è stato allegato, per permettere confronti equivalenti
    // srand((unsigned)time(NULL));
    //  FILE *f = fopen("data.csv", "w+");
    //  int size=100;
    //  for (int j = 0; j < size; j++) {
    //      for (int i = 0; i < n; i++) {
    //          int v = 0;             
    //         //  v=(int)(100000*exp(-(0.0+i-n/2)*(0.0+i-n/2)/n/n*64));
    //         //  v=(int)(5000*(1+sin(3.1415*(i/(n/2.0)))));
    //          v=(int)(10000*sin(3.1415*(((int)(i/30))*30/(n+0.0))));
    //          v+=(rand()%2*2-1)*rand()%(3+(int)(2*n*pow(((i+0.0)/n),2)));
    //          fprintf(f, "%d,", v);
    //      }
    //      fprintf(f, "\n");
    //  }
    //  fclose(f);

    ifstream input_data;
    input_data.open("data.csv");
    if (!input_data) { cerr << "Impossibile aprire data.csv" << endl; delete[] B; delete[] A; return 1; }

    int read_min = -1;
    int read_max = -1;
    long read_avg = 0;

    //// lancio ntests volte per coprire diversi casi di input random
    for (test = 0; test < ntests; test++) {

        /// inizializzazione array: numeri random con range dimensione array
        for (i = 0; i < n; i++) {
            char comma;
            if (!(input_data >> A[i] >> comma) || comma != ',') {
                cerr << "Dataset non valido" << endl; delete[] B; delete[] A; return 1;
            }
        }

        if (details) {
            printf("caricato array di dimensione %d\n", n);
            print_array(A, n);
        }

        ct_swap = 0;
        ct_cmp = 0;
        ct_read = 0;

        /// algoritmo di sorting
        radix_sort(A, B, n);
	if (isSorted(A, n))
	  cout << "Array ordinato correttamente" << endl;
	else
	  cout << "ERRORE: array non ordinato" << endl;
        if (details) {
	  printf("Output:\n");
	  print_array(A, n);
        }

        /// statistiche
        read_avg += ct_read;
        if (read_min < 0 || read_min > ct_read)
	  read_min = ct_read;
        if (read_max < 0 || read_max < ct_read)
	  read_max = ct_read;
        printf("Test %d %d\n", test, ct_read);
    }

    printf("N test: %d, Min: %d, Med: %.1f, Max: %d\n",
           ntests,
           read_min, (0.0 + read_avg) / ntests, read_max);

    delete[] B;
    delete[] A;

    return 0;
}
