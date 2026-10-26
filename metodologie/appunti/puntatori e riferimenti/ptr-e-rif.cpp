// Puntatori e riferimenti

/*
  Possiamo riferirci ad un oggetto per nome, in C++ gran parte degli
  oggetti ha "un'identità", ovvero risiede a uno specifico indirizzo di
  memoria, un oggetto è accessibile conoscendo l'indirizzo ed il tipo, i
  puntatori ed i riferimenti ci permettono di contenere ed usare gli
  indirizzi.

  Puntatori
  Un puntatore è un contenitore di un altro indirizzo di memoria, può
  essere vista come una variabile che contiene per l'appunto un altro
  indirizzo di memoria, l'operazione fondamentale del puntatore è il
  deferimento che ci permette di ovvero riferirsi all'oggetto a cui
  punta il puntatore.
  In generale per un tipo T, T* è il puntatore a T, T* p contiene
  l'indirizzo di un oggetto di tipo T
*/


#include <iostream>

// funzione di test di puntatore a void
void f(int* pi){
  void* pv = &pi; // conversione implicita da int* a void*
  // *pv;            // impossibile dereferire void*
  // ++pv;           // impossibile incrementare il puntatore la
		  // dimensione dell'oggetto puntato e sconosciuta
}

int main(){
  
  
  // dichiariamo un tipo char 
  char c = 'b';
  // puntatore di tipo char 
  char* pc = &c;
  // con l'operatore & è possibile riferisi all'indirizzo di memoria di pc
  std::cout << "Indirizzo del puntatore: " << &pc << std::endl;
  // andiamo a stampare il contenuto di pc = indirizzo di memoria di c
  // e successivamente si va a dereferenziarne il contenuto con
  // l'operatore prefisso *
  std::cout << "sono pc ed il mio contenuto è: "<< pc << ", punto a c che contiene : " << *pc << std::endl;

  // il puntatore se non diversamente specificato ci permette di
  // modificare il contenuto dell'oggetto puntato
  int x = 10;
  std::cout << "contenuto di x prima della modifica: " << x  << std::endl;
  int* px = &x;
  *px *=2;
  std::cout << "x dopo la modifica utilizzando il puntatore ad x:" << x << std::endl; // stampa 20

  /* 
     nel codice di basso livello è necessario memorizzare o passare un
     indirizzo di una posizione in memoria senza sapere quale tipo di
     oggetto vi sia memorizzato, a questo scopo possiamo utilizzare il
     puntatore a void , void*  (no puntatore a funzione o membro)
  */
  
  f(px);  // genera errore in fase di compilazione perchè sto cercando
	  // di dereferire un tipo void*

  
  //  nullptr è un tipo letterale che può essere assegnato ad un
  //  puntatore, che significa che il puntantore non punta a nessun
  //  oggetto.

  int* ptr_i = nullptr;  // ptr a nullptr
  char* ptr_c = nullptr; // ptr a nullptr

  // non è possibile dereferenziare i puntatori nulli, genererebbe un
  // errore di segmentation faul (accesso a memoria che non gli
  // appertiene) , NO *ptr_i NO *ptr_c , non possiamo
  std::cout << "ptr_i: " << ptr_i << "\n" //stampa 0
            << "ptr_c:" << ptr_c << std::endl; // non stampa alcun valore
 
  
  return 0;
}

