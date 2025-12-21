// ============================================================================
// Appunti sul libro di Stroustrup
// Autore: Luca Chierchia
// ============================================================================
//
// Note:
// - Tutto ciò che segue in commenti è testo esplicativo
// - Il codice è eseguibile senza toccare il file
// - Separazione chiara per la stampa: righe "===="
//
// ============================================================================


// Argomenti di ripasso
/*  B. Stroustrup
    C++: Linguaggio, libreria standard, principi di programmazione
    Quarta edizione, Pearson, 2015.

    Capitolo 6:  Tipi e dichiarazioni
    


    Tipi fondamentali
    Il C++ ha un set di tipi fondamentali corrispondenti alle più comuni
    unità di base di memorizzazione di un computer:
    -booleani, tipo booleano (true e false)
    -char, tipi carattere
    -int, i tipi interi
    -double, sono i tipi in virgola mobile
    -void, per indicare l'assenza di informazioni
*/

// I tipi int,bool e char sono detti collettivamente tipi integrali.


#include <iostream>


// Tipi Booleani

void f(int a, int b){
  bool b1(a==b);
  std::cout << b1 << std::endl;
};

// Un utilizzo comune di bool è come tipo di ritorno di una funzione
// che verifica un predicato
bool greater(int a,int b){
  return a > b;
}

// funzione di test dichiarato e definita dopo f() e greater()
// altrimenti il compilatore segnalerebbe un errore in fase di
// compilazione  perchè non riuscirebbe a trovare le funzioni da
// includere in test01()
void test01(int a, int b){
  f(a,a); // se a è uguale a b allora stampa 1
  f(a,b); //  se a è diverso da b allora stampa 0
  greater(a,b); // se a è maggiore di b ritorna 1
  greater(b,a); // se a è minore di b ritorna 0
}

// Tipi Carattere

/*
  Sono utilizzati molti set di caratteri e codifiche di set, infatti il
  c++  fornisce numerosi tipi di carattere:
  - char, tipo di carattere predefinito, di solito ad 8 bit 
  - signed char, carattere con segno
  - unsigned char, carattere senza segno
  - wchar_t, fornisce un set di caratteri più ampio (come Unicode)
  - char16_t, tipi per contenere set di caratteri da 16 bit, come UTF-16
  - char32_t, tipi per conentere set di caratteri da 32 bit, come UTF-32 

*/

// Ciascun carattere ha un valore intero nel set di caratteri usato dall'implementazione, nella seguente funzione è si ottiene il corrispettivo valore intero di un carattere.
void intval(){
  int count = 0;
  for(char c; std::cin >> c;){
    if(c == 'e')
      ++count;
    if(count == 3)
      break;
    std::cout << "tha value of" << " c" << " is " << int{c} << "\n" ;
  }
}

// la seguente funzione evidenzia come è possibile operare con le operazioni aritmetiche con i tipi carattere, il letterale carattere '0' viene convertito nel suo valore interoe viene sommato ad i
void digits(){

  // ciclo con static_cast il carattere '0' ha valore intero = 48, sommando
  for(int i = 0; i != 10; ++i)
    std::cout << static_cast<char>('0'+i) << std::endl;

  // ciclo con omissione del cast
   for(int i = 0; i != 10; ++i)
    std::cout << ('0'+i) << std::endl;
  
 }

// Tipi Interi

/*

Ciascun tipo intero può avere tre forme: int "semplice", signed int, unsigned int.
Inoltre gli interi hanno quattro dimensioni short, int, long.
E possibile combinare le dimensioni del tipo con le forme signed, unsigned ed int semplice, per esempio: short int, long unsigned int , long int, signed int, etc.

 */

/*

  NARROWING
  il narrowing in C++ la conversione implicita di un tipo di dato
  più grande in un tipo di dato più piccolo con la conseguente perdita
  di dati (conversione per restringimento)

  CONVERSIONI IMPLICITE
  le conversioni implicite sono le conversioni attuate dal compilatore
  in maniera automatica.

  ARITMETICA && ESPRESSIONI LOGICHE bit a bit
  - I booleani vengono convertiti in int, quindi le espressioni vengono
  eseguiti su valori convertiti (1 e 0), successivamente se il risultato
  torna ad essere un booleano come nell'esempio es1

  - i tipi carattere essendo dei tipi integrali, sono valide le operazioni aritmetiche e bit a bit logiche

*/


int main(){

  // Sezione codice per tipi booleani
  std::cout << "primo test:" << std::endl;
  test01(3,3);
  std:: cout << "secondo test:" << std::endl;
  test01(5,2);

  bool b2 {"c"}; // conversione da const char* -> bool
  // bool b3 {4}; // errore di compilazione {} questa sintassi dovrebbe
	       // prevenire il narrowing e per l'appunto la perdita di
	       // informazione che in questo caso non è consentita
  bool b31 = 4; // in questo caso b31 = 1 dato che 4 != 0
  bool b4 {1}; // viene inizializzato correttamente

  // es1
  bool a = true; 
  bool b = true; 
  bool z = a-b; // z sarà false perchè l'operazione viene effettuata
		// sulla conversione ad interi, quindi 1-1 = 0, viene
		// poi nuovamente convertito in in booleano.
  

  // Sezione codice per tipi carattere

  
  char c = 'e'; // assegnazione del carattere e al char c 
  signed char c1 = -33; // assegnamento di c1 = 33 -> stampa \337
  unsigned char c2 = 98; // conversione implicta di 98 in 'b'

  std::cout << "c = " << c << "\n" << "c1 = " << c1 << "\n" << "c2 = " << c2 << std::endl;

  // funzione che converte il carattere in corrispettivo intero
  // intval();
  digits();


  // Sezione codice tipi int

  unsigned int x = -12;
  signed int y = 3;
  short int s = 10;
  long unsigned int lsi = 12132323;

  std::cout << "dimensioni di x " << sizeof(x) << "\n"  // dimensione di un int 4 byte
            << "dimensione di y " << sizeof(y) << "\n"  // come sopra
            << "dimensione di s " << sizeof(s) << "\n"  // dimensione di un short int 2 byte
            << "dimensione di lsi " << sizeof(lsi) << std::endl; // dimensione di un long int 8 byte
  
  
  return 0;
}



