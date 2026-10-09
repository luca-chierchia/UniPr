#include <iostream>

// ==================================================
// 1. INDIRIZZI DI MEMORIA
// ==================================================

// Una variabile identifica un oggetto di un certo tipo.
// L'operatore & permette di ottenere il suo indirizzo.
//
// Esempio:
// int x = 10;
// &x -> indirizzo di memoria di x


// ==================================================
// 2. PUNTATORI: DICHIARAZIONE E INIZIALIZZAZIONE
// ==================================================

// Un puntatore è un oggetto che può memorizzare
// l'indirizzo di un altro oggetto.
//
// int *p = &x;
//
// p  -> indirizzo memorizzato nel puntatore
// &p -> indirizzo del puntatore stesso
// *p -> oggetto puntato


// ==================================================
// 3. DEREFERENZIAZIONE
// ==================================================

// L'operatore * permette di accedere all'oggetto
// attraverso un puntatore valido.
//
// *p = 20;
//
// Modifica direttamente l'oggetto puntato.


// ==================================================
// 4. PUNTATORI NULLI
// ==================================================

// nullptr rappresenta un valore di puntatore nullo.
//
// int *p = nullptr;
//
// Non bisogna dereferenziare un puntatore nullo.


// ==================================================
// 5. REFERENCE
// ==================================================

// Una reference è un alias di un oggetto.
//
// int &r = x;
//
// Modificare r significa modificare x.
//
// Una reference deve essere inizializzata
// e non può essere ricollegata a un altro oggetto.


// ==================================================
// 6. PUNTATORI E CONST
// ==================================================

// const int *p
// Puntatore modificabile a int const.
//
// int *const p = &x
// Puntatore const a int modificabile.
//
// const int *const p = &x
// Puntatore const a int const.
//
// Il qualificatore const applicato all'accesso
// tramite puntatore non rende necessariamente
// const l'oggetto originale.


// ==================================================
// 7. PUNTATORI E REFERENCE COME PARAMETRI
// ==================================================

// Passaggio per valore.
// La funzione modifica soltanto una copia.

void modifica_valore(int x) {
    x += 10;
}


// Passaggio di un puntatore per valore.
// Viene copiato l'indirizzo dell'oggetto.
//
// Dereferenziando il puntatore possiamo
// modificare l'oggetto originale.

void modifica_puntatore(int *p) {

    if (p != nullptr) {
        *p += 10;
    }
}


// Passaggio per riferimento.
// x è un alias dell'oggetto originale.

void modifica_reference(int &x) {
    x += 10;
}


// ==================================================
// 8. LIFETIME E DANGLING POINTER/REFERENCE
// ==================================================

// ESEMPIO ERRATO: NON UTILIZZARE

/*
int *ritorna_puntatore_errato() {

    int numero = 10;

    return &numero;
}
*/

// numero è una variabile locale.
//
// Al termine della funzione il suo lifetime termina.
//
// Il puntatore restituito diventa dangling.
//
// Dereferenziarlo provoca comportamento indefinito.


// ==================================================
// MAIN
// ==================================================

int main() {

    // ----------------------------------------------
    // 1. INDIRIZZI DI MEMORIA
    // ----------------------------------------------

    double var = 23.454;

    std::cout << "Valore di var: "
              << var << '\n';

    std::cout << "Indirizzo di var: "
              << &var << '\n';


    // ----------------------------------------------
    // 2. DICHIARAZIONE DEI PUNTATORI
    // ----------------------------------------------

    int x = 12;

    int *ptr_x = &x;

    std::cout << "\nValore di x: "
              << x << '\n';

    std::cout << "Indirizzo di x: "
              << &x << '\n';

    std::cout << "Indirizzo memorizzato in ptr_x: "
              << ptr_x << '\n';

    std::cout << "Indirizzo del puntatore ptr_x: "
              << &ptr_x << '\n';


    // ----------------------------------------------
    // 3. DEREFERENZIAZIONE
    // ----------------------------------------------

    std::cout << "\nValore puntato: "
              << *ptr_x << '\n';

    *ptr_x += 8;

    std::cout << "Nuovo valore di x: "
              << x << '\n'; // 20


    // ----------------------------------------------
    // 4. PUNTATORI NULLI
    // ----------------------------------------------

    int *ptr2_x = nullptr;

    if (ptr2_x == nullptr) {
        std::cout << "\nptr2_x e' nullo\n";
    }

    ptr2_x = &x;

    if (ptr2_x != nullptr) {
        *ptr2_x -= 8;
    }

    std::cout << "Valore di x: "
              << x << '\n'; // 12


    // ----------------------------------------------
    // 5. REFERENCE
    // ----------------------------------------------

    int &y = x;

    y++;

    std::cout << "\nValore di x: "
              << x << '\n'; // 13

    std::cout << "Valore di y: "
              << y << '\n'; // 13

    std::cout << "Indirizzo di x: "
              << &x << '\n';

    std::cout << "Indirizzo tramite y: "
              << &y << '\n';


    // ----------------------------------------------
    // 6. PUNTATORI E CONST
    // ----------------------------------------------

    int j = 10;
    int k = 20;

    // Puntatore a int const

    const int *ptr_j = &j;

    // *ptr_j = 30; // ERRORE

    ptr_j = &k; // CORRETTO


    // Puntatore const a int

    int *const ptr_k = &k;

    *ptr_k = 30; // CORRETTO

    // ptr_k = &j; // ERRORE


    // Puntatore const a int const

    const int *const ptr2_j = &j;

    // *ptr2_j = 40; // ERRORE
    // ptr2_j = &k;  // ERRORE

    j = 40; // CORRETTO


    // ----------------------------------------------
    // 7. PASSAGGIO DEI PARAMETRI
    // ----------------------------------------------

    int numero = 10;

    modifica_valore(numero);

    std::cout << "\nDopo modifica_valore: "
              << numero << '\n'; // 10


    modifica_puntatore(&numero);

    std::cout << "Dopo modifica_puntatore: "
              << numero << '\n'; // 20


    modifica_reference(numero);

    std::cout << "Dopo modifica_reference: "
              << numero << '\n'; // 30


    // ----------------------------------------------
    // 8. DANGLING POINTER
    // ----------------------------------------------

    // Non dereferenziare puntatori dangling.
    //
    // Non utilizzare indirizzi di oggetti
    // il cui lifetime è terminato.

    return 0;
}