#include <iostream>

// ============================================================================
// CHEATSHEET C++: MODIFICATORI, QUALIFICATORI E TIPI PRIMITIVI
// ============================================================================

// I tipi di dato primitivi possono avere qualificatori e/o modificatori
// che alterano le dimensioni ed il segno del tipo (modificatori di tipo)
// oppure il comportamento in memoria (qualificatori di tipo).
// In totale abbiamo 6 keyword principali combinabili tra loro.

// Modificatori di segno:
// signed: memorizza sia valori positivi che negativi (default per interi)
// unsigned: forza la variabile a memorizzare solo valori maggiori o uguali a zero.

// Modificatori di dimensione:
// short: riduce la dimensione minima occupata in memoria da un intero (min 2 byte)
// long: aumenta la dimensione minima occupata in memoria rispetto al tipo base
// long long: introdotto per garantire interi ad altissima capacità (min 8 byte)

// Qualificatori di tipo (CV-qualifiers):
// const: rende l'oggetto immutabile dopo la sua inizializzazione (errore a compile-time se modificato)
// volatile: impedisce al compilatore di ottimizzare le letture/scritture su questa variabile

int main() {

    // ============================================================================
    // 1. TIPI DI DATO PRIMITIVI SEMPLICI
    // ============================================================================

    int a = 2;              // Intero con segno (default): tipicamente 4 byte [da -2B a +2B]
    float b = 2.5f;         // Virgola mobile a singola precisione (con segno sempre): 4 byte
    double c = 45.44656;    // Virgola mobile a doppia precisione (con segno sempre): 8 byte
    bool t = true;          // Booleano: 1 byte (0 è false, qualsiasi altro valore è true)
    char ch = 'a';          // Singolo carattere (apici singoli): 1 byte

    // Stringa C-like (Array di caratteri): inserisce automaticamente il terminatore nullo '\0'
    // Memoria: ['C', 'a', 'n', 'e', '\0'] -> Dimensione totale occupata = 5 byte
    char animale[] = "Cane";


    // ============================================================================
    // 2. COMBINAZIONI DI KEYWORD (Esempi pratici)
    // ============================================================================

    // Costante Intera Senza Segno (Combina: const + unsigned + int)
    // Non può essere modificata e memorizza solo valori positivi (da 0 a 4.294.967.295)
    const unsigned int GIORNI_ANNO = 365;
    // GIORNI_ANNO = 366; // <--- Togliere il commento genererebbe un errore di COMPILAZIONE

    // Costante di tipo double esteso (Combina: const + long + double)
    const long double PI_GRECO_PRECISO = 3.14159265358979323846L;


    // ============================================================================
    // 3. EFFETTO DEI MODIFICATORI DI DIMENSIONE IN MEMORIA
    // ============================================================================

    short int intero_corto = 10;          // Ridotto: garantito minimo 2 byte
    long int intero_lungo = 999999;       // Esteso: garantito minimo 4 byte
    long long int intero_enorme = 123456789012345LL; // Massimo: garantito minimo 8 byte


    // ============================================================================
    // STAMPA DEI REQUISITI DI MEMORIA (sizeof)
    // ============================================================================

    std::cout << "--- Tipi Base ---\n"
              << "Dimensione int: "          << sizeof(a)       << " byte\n"
              << "Dimensione float: "        << sizeof(b)       << " byte\n"
              << "Dimensione double: "       << sizeof(c)       << " byte\n"
              << "Dimensione bool: "         << sizeof(t)       << " byte\n"
              << "Dimensione char: "         << sizeof(ch)      << " byte\n"
              << "Dimensione array stringa: "<< sizeof(animale) << " byte\n\n"

              << "--- Tipi Combinati e Modificati ---\n"
              << "Dimensione const unsigned int: " << sizeof(GIORNI_ANNO)       << " byte\n"
              << "Dimensione const long double: "  << sizeof(PI_GRECO_PRECISO)  << " byte\n"
              << "Dimensione short int: "          << sizeof(intero_corto)      << " byte\n"
              << "Dimensione long int: "           << sizeof(intero_lungo)      << " byte\n"
              << "Dimensione long long int: "      << sizeof(intero_enorme)     << " byte\n";

    return 0;
}
