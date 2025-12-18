/*
  Array e puntatori
  Per un tipo T, T[size] è il tipo di array di size
  elementi di tipo "T"

  Un array è un modo fondamentale del C++ di
  rappresentare una sequenza di oggetti in memoria,
  l'array memorizza in celle contigue di memoria
  della dimensione adatta all'entità da memorizzare.

  L'array incorporato del C++ è un costrutto
  intrensicamente di basso livello, che dovrebbe
  essere usato entro l'implementazione di strutture
  dati di più alto livello.
  - Non è possibile l'assegnamento agli array
  - Il nome di un array si converte implicitamente in
  un puntatore al primo elemento dell'array

  Un array può essere allocato nello stack  e nella
  memoria dinamica, ha sempre dimensione fissa.
*/

#include <iostream>
#include <vector>

void g(int* a, int n){
  int* ptr_s = a;
  int* ptr_end = a + n;
  while(ptr_s != ptr_end){
    std::cout << "[" << *ptr_s << "]" ;
    ++ptr_s;
  }
  std::cout << "\n" ;
}

void f(){
  int aa[10]; 
  aa[6] = 9;
  int x = aa[99]; // comportamento indefinito
}

void g(int n){
  int arr[n]; // NO, genera errore in fase di
	      // compilazione
  //vector<int> v1(n); // OK, vettore di n elementi
}

int main(){
  
  float v[3];  // array di di 3 float
  char* a[30]; // un array di 30 puntatori di tipo
	       // char

  // inizializzazione degli array
  int a1[] = {1,2,3,4}; // array di 4 elementi, la dimensione
		       // dell'array corrisponde al numero degli
		       // elementi inizializzati nelle {}
  int a2[10]={1};    // array di 10 elementi, a2[0] = 1, gli altri
		      // elementi vengono inizializzati a 0

  g(a1,4);
  g(a2,10);
  return 0;
}




