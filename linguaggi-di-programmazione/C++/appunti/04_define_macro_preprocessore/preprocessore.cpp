#include <iostream>

/*
 * PREPROCESSORE
 *
 * Il preprocessore viene eseguito prima della compilazione.
 *
 * Elabora le direttive che iniziano con '#', tra cui:
 *
 * #include  -> include un header
 * #define   -> definisce una macro
 * #ifdef    -> verifica se una macro è definita
 * #ifndef   -> verifica se una macro NON è definita
 * #if       -> compilazione condizionale
 * #endif    -> termina il blocco condizionale
 *
 * Dopo il preprocessing, il codice risultante viene passato
 * al compilatore.
 */

// attenzione alle macro quando scriviamo:
// #define MIA_MACRO val;
// non dobbiamo mai includere il punto e virgola alla fine
// dato che andrebbe a rimpiazzare anche il ;
/*
 * Ad esempio, #define VALORE 5;
 * int x = VALORE + VALORE;
 * diventa int x = 5;+ 5;;
 * generando ovviamente errore in fase di compile-time
 */
#define MIA_SOMMA (5 + 1)
#define DEBUG_ON

int main() {

    int x = MIA_SOMMA * MIA_SOMMA;

    std::cout << "x: " << x << '\n';

// per disabilitare la modalità DEBUG_ON va commentato il #define DEBUG_ON
#ifdef DEBUG_ON
    std::cout << "[DEBUG] Valore di x: " << x << '\n';
#endif

    return 0;
}