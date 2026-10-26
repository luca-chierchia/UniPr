#include <iostream>

//Dichiarare un tipo di dato per rappresentare le stagioni dell'anno, successivamente scrivere una funzione che restituisce la stagione dell'anno letta in input. La funzione deve essere del tipo dichiarato del tipo di dato.
enum seasons { autunno, inverno, primavera, estate};

seasons leggiStagione(){
  int stag;
  do{
  std::cout << "Scegli la stagioen : 0 = autunno, 1 = inverno, 2 = primavera, 3 = estate\n";
  std::cin >> stag;
  }while(stag < 0 || stag > 3);

  return static_cast<seasons>(stag);
  
}

void visualizzaStagione(seasons s){
  switch (s){
  case autunno:
    std::cout << "autunno";
    break;
  case inverno:
    std::cout << "inverno";
    break;
  case primavera:
    std::cout << "primavera";
    break;
  case estate:
    std::cout << "estate";
    break;
  }

}

int main(){
  seasons stagioneLetta = leggiStagione();
  std::cout << "Siamo in  " ;
  visualizzaStagione(stagioneLetta);
  std::cout <<  "\n";
  return 0;
}
