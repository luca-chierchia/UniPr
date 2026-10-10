#include <iostream>

/*
 * OPERATORI ED ESPRESSIONI
 *
 * C++ è un linguaggio a tipizzazione statica:
 * il tipo di una variabile viene determinato a compile-time
 * e non cambia durante la sua vita.
 *
 * Sono tuttavia possibili conversioni implicite ed esplicite
 * tra tipi compatibili.
 */

int main() {

    int x = 10;
    int y = 3;

    // ==================================================
    // OPERATORI ARITMETICI
    // ==================================================

    // +    addizione
    // -    sottrazione
    // *    moltiplicazione
    // /    divisione
    // %    resto della divisione

    int z = x + y;       // 13
    int prodotto = x * y; // 30
    int resto = x % y;    // 1

    // * / % hanno precedenza su + -
    int risultato = 2 + 3 * 4;      // 14

    // Le parentesi permettono di modificare l'ordine
    int risultato2 = (2 + 3) * 4;   // 20


    // ==================================================
    // INCREMENTO E DECREMENTO
    // ==================================================

    int a = 2;
    int b = 2;

    // Pre-decremento:
    // prima modifica il valore, poi restituisce il nuovo valore.
    std::cout << --a << '\n';    // 1

    // Post-incremento:
    // restituisce il vecchio valore, poi incrementa la variabile.
    std::cout << b++ << '\n';    // stampa 2

    std::cout << b << '\n';      // ora b vale 3


    // ==================================================
    // OPERATORI RELAZIONALI
    // ==================================================

    // ==    uguale
    // !=    diverso
    // <     minore
    // >     maggiore
    // <=    minore o uguale
    // >=    maggiore o uguale

    bool confronto = x > y;

    if (x > y) {
        std::cout << "x è maggiore di y\n";
    } else {
        std::cout << "x non è maggiore di y\n";
    }


    // ==================================================
    // OPERATORI LOGICI
    // ==================================================

    // &&    AND
    // ||    OR
    // !     NOT

    bool p = true;
    bool q = false;

    if (p && !q) {
        std::cout << "Condizione vera\n";
    }

    // Nei contesti booleani gli interi vengono convertiti:
    //
    // 0          -> false
    // diverso da 0 -> true

    int numero = 5;

    if (numero) {
        std::cout << "numero è diverso da zero\n";
    }


    // ==================================================
    // OPERATORI DI ASSEGNAMENTO
    // ==================================================

    x = 2;

    x += 5;     // x = x + 5
    x -= 2;     // x = x - 2
    x *= 10;    // x = x * 10
    x /= 2;     // x = x / 2
    x %= 3;     // x = x % 3


    // ==================================================
    // OPERATORE TERNARIO
    // ==================================================

    int j = (x % 2 == 0) ? 100 : 0;

    // equivalente concettualmente a:
    //
    // if (x % 2 == 0)
    //     j = 100;
    // else
    //     j = 0;


    // ==================================================
    // CONVERSIONI IMPLICITE
    // ==================================================

    double d = 5.8;

    int n = d;

    // d rimane un double contenente 5.8.
    // Il valore viene convertito in int per inizializzare n.
    // La parte frazionaria viene scartata:
    //
    // n = 5

    // ==================================================
    // CASTING
    // ==================================================
    int x1 = 13;
    int y1 = 5;
    float r = static_cast<float> (x1)/y1; // r =  casting di x in float e diviso per y
    std::cout << r;

    return 0;
}