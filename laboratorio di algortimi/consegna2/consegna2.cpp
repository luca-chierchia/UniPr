#include <iostream>
using namespace std;

struct Node{
  int value;
  Node *left;
  Node *right;
  Node(int v) : value(v), left(nullptr), right(nullptr){}
};

// distruzione dei nodi
void destroyNode(Node *n){
  if(n == nullptr)
    return;
  destroyNode(n->left);
  destroyNode(n->right);
  // debug?
  //  cout << "hai distrutto il nodo di valore " << n->value << "\n";
  delete n;
}

void printPreorder(Node *n){
  if(n == nullptr){
    cout << "- ";
    return;
  }
  cout << n->value << " " ;
  printPreorder(n->left);
  printPreorder(n->right);
}
// ausiliaria: scambia i due puntatori figlio di UN nodo
void swapChildren(Node *n){
  Node *tmp = n->left;
  n->left = n->right;
  n->right = tmp;
}


// attraversamento: applica lo scambio a ogni nodo
void flip(Node *n){
  if(n == nullptr) return;   // caso base: albero vuoto
  swapChildren(n);
  flip(n->left);
  flip(n->right);
}


int main(){
  // Albero vuoto
  Node* vuoto = nullptr;

  // Un solo nodo
  Node* uno = new Node(1);

  // 3) Catena di 3 nodi (sbilanciato, non completo)
  Node* catena = new Node(1);
  catena->left = new Node(2);
  catena->left->left = new Node(3);

  // Completo e bilanciato (7 nodi)
  //          1
  //        /   \
  //       2     3
  //      / \   / \
  //     4   5 6   7
  Node* completo = new Node(1);
  completo->left = new Node(2);
  completo->right = new Node(3);
  completo->left->left = new Node(4);
  completo->left->right = new Node(5);
  completo->right->left = new Node(6);
  completo->right->right = new Node(7);

  // Bilanciato ma NON completo (buco a sinistra nell'ultimo livello)
  //          1
  //        /   \
  //       2     3
  //        \
  //         4
  Node* incompleto = new Node(1);
  incompleto->left = new Node(2);
  incompleto->right = new Node(3);
  incompleto->left->right = new Node(4);

  // Stampa di controllo
  cout << "vuoto: ";
  printPreorder(vuoto);
  cout << endl;
  cout << "uno: ";
  printPreorder(uno);
  cout << endl;
  cout << "catena: ";
  printPreorder(catena);
  cout << endl;
  cout << "completo: ";
  printPreorder(completo);
  cout << endl;
  cout << "incompleto: ";
  printPreorder(incompleto);
  cout << "\n";
  printPreorder(completo);
  cout << "\n";
  flip(completo);
  printPreorder(completo);

  // Qui chiamerai le tue funzioni, ad esempio:
  // cout << isBalanced(catena) << endl;

  destroyNode(uno);
  destroyNode(catena);

  destroyNode(completo);
  destroyNode(incompleto);
    

  return 0;
}
