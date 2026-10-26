// Ambiti di visibilità

/*
  Una dichiarazione introduce un nome in un certo
  ambito, esistono diversi ambiti di visibilità
  (scope) ed in base a dove viene dichiarata
  l'entità cambia la sua visibiltià ovvero la
  possibilità di poter utilizzare tale entità.

  tipologie di ambiti di visibilità:
  - ambito locale,
  - ambito globale,
  - ambito di clase,
  - ambito dell'istruzione,

*/

#include <iostream>

// ambito globale
int x = 1; // x è visibile ovunque nel file

// ambito di classe
class Pippo{
public:
  int x = 11; // la variabile x è visibile solo
	      // interna alla classe e non
	      // all'esterno, motivo per cui non
	      // va in collissione con la x
	      // globale
  
  
};


int main(){
  std::cout << x << std::endl; // stampa 1

  Pippo p;
 
  // ambito locale, nell'ambito locale è possibile
  // accedere alle entità dichiarate esterne al blocco 
  {
    // la variabile x interna al blocco di
    // parentesi {} va a nascondere la x globale,
    // questo concetto prendo il nome di shadowing
    int x = 12;
    std::cout << "Sono la x di scope locale {}: " << x << std::endl; // stampa 12
    
    std::cout << "Sono la x dell'oggetto Pippo: " <<  p.x << std::endl; // stampa 11
    std::cout << "Sono all'interno del blocco {}, ma utilizzo :: per chiamare la x globale: " << ::x << std::endl;
  }

  // fuori da un blocco {} non è possibile avere
  // accesso a ciò che è stato dichiarato al suo
  // interno
  
  std::cout << "Mi trovo nel main e sono la x globale:  "  << x << std::endl; // stampa 1

  // ambito di istruzione
  // un nome è nell'ambito dell'istruzione se è
  // definito entro la parte tra parentesi () di
  // un istruzione if,while,for o switch

  std::cout << "Sono la x del ciclo for: " ;
  for( int x = 20; x != 0; --x){
    if(x == 1)
      std::cout << x << std::endl;
    std::cout << x << " " ;
  }

  if(int x = 100)
    std::cout << "Sono x dell'istruzione if, " << x << std::endl;
  
  return 0;
}
