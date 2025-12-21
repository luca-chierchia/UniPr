#include <iostream>
// file2.cpp

double d = 2.34;
extern char c2;
extern int global_counter;
extern char c;
extern double b;
extern int x;         
int f();

void incrementGlobalCounter();
void incrementInternalCounter();
void printFileState();
int castTheMagic();

void g(){
  x += f();
  std::cout << x << "\n" ;
};

int main(){
  std::cout << "Tutto ok" << "\n" ;
  std::cout << c2 << "\n" << d << "\n" ;
  std::cout << "[file2] iniziale gloabal_counter:" << global_counter << "\n" ;
  incrementGlobalCounter();
  incrementGlobalCounter();
  incrementGlobalCounter();
  incrementInternalCounter(); // Attenzione leggere il commento in fondo.
  printFileState();
  std::cout << "[file2] dopo gloabal_counter:" << global_counter << "\n" ;
  std::cout << " See my magic: " << castTheMagic() << std::endl;
  return 0;
}

/*
  Nota 1:
  Anche se la variabile internal_counter è dichiarata come static in file1.cpp
  (quindi ha linkage interno ed è visibile solo in quella unità di traduzione),
  essa può comunque essere modificata indirettamente dall’esterno tramite una
  funzione definita in file1.cpp (es. incrementInternalCounter) che ha linkage
  esterno.

  In file2.cpp noi NON accediamo direttamente a internal_counter (non potremmo),
  ma invochiamo una funzione “pubblica” del modulo file1.cpp. La funzione, al
  suo interno, incrementa internal_counter e printFileState() mostra lo stato
  interno aggiornato del modulo file1.cpp.

  Nota 2:
  Il linkage non è bidirezionale: stabilisce quali nomi sono visibili tra unità
  di traduzione.
  Una funzione con linkage esterno può operare su entità con linkage interno
  definite nella stessa unità di traduzione, ma tali entità restano inaccessibili
  dall’esterno.
*/

