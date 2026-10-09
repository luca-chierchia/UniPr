#include <iostream>
#include <string>

/*
 * ==================================================
 * FUNZIONI
 * ==================================================
 *
 * Una funzione è un blocco di codice riutilizzabile
 * che può ricevere parametri e restituire un valore.
 *
 * Sintassi generale:
 *
 * tipo_ritorno nome_funzione(parametri) {
 *     // istruzioni
 * }
 *
 * Una funzione può:
 * - ricevere zero o più parametri;
 * - restituire un valore;
 * - non restituire alcun valore (void);
 * - richiamare altre funzioni;
 * - richiamare sé stessa (ricorsione).
 */


// ==================================================
// DICHIARAZIONE / PROTOTIPO
// ==================================================

/*
 * La dichiarazione comunica al compilatore
 * l'esistenza e l'interfaccia della funzione.
 *
 * La definizione contiene il corpo della funzione.
 *
 * Se una funzione viene utilizzata prima della sua
 * definizione, deve essere stata precedentemente
 * dichiarata.
 */

int somma(int a, int b);


// Definizione della funzione

int somma(int a, int b) {
    return a + b;
}


// ==================================================
// FUNZIONI VOID
// ==================================================

/*
 * void indica che la funzione non restituisce
 * alcun valore al chiamante.
 */

void print_hello_my_name(const char* nome) {
    std::cout << "Hello " << nome << '\n';
}


// ==================================================
// FUNZIONI CON VALORE DI RITORNO
// ==================================================

/*
 * return termina l'esecuzione della funzione
 * e, nelle funzioni non void, fornisce un valore
 * al chiamante.
 */

int max_of_two(int a, int b) {

    if (a >= b) {
        return a;
    }

    return b;
}


// ==================================================
// PASSAGGIO PER VALORE
// ==================================================

/*
 * Nel passaggio per valore, il parametro viene
 * inizializzato a partire dall'argomento ricevuto.
 *
 * Le modifiche al parametro non modificano
 * l'oggetto originale del chiamante.
 */

void incrementa_valore(int x) {
    x++;
}


// ==================================================
// PASSAGGIO PER REFERENCE
// ==================================================

/*
 * Una reference è un alias di un oggetto.
 *
 * La funzione opera direttamente sull'oggetto
 * originale attraverso il riferimento.
 *
 * Le modifiche sono quindi visibili al chiamante.
 */

void incrementa_reference(int& x) {
    x++;
}


// ==================================================
// PASSAGGIO PER CONST REFERENCE
// ==================================================

/*
 * const T& permette di accedere a un oggetto
 * senza copiarlo e senza modificarlo attraverso
 * il riferimento.
 *
 * È particolarmente utile per oggetti
 * potenzialmente costosi da copiare.
 */

void stampa_nome(const std::string& nome) {
    std::cout << nome << '\n';
}


// ==================================================
// PARAMETRI DI DEFAULT
// ==================================================

/*
 * Un parametro può avere un valore predefinito.
 *
 * Se l'argomento viene omesso durante la chiamata,
 * viene utilizzato il valore di default.
 *
 * Nella dichiarazione, dopo un parametro con
 * valore di default, anche i parametri successivi
 * devono avere un valore di default.
 */

void print_auguri(
    const char* nome,
    const char* auguri = "Auguri"
) {
    std::cout << auguri << " " << nome << '\n';
}


// ==================================================
// FUNCTION OVERLOADING
// ==================================================

/*
 * L'overloading permette di definire più funzioni
 * con lo stesso nome ma parametri differenti.
 *
 * Il compilatore seleziona l'overload appropriato
 * in base agli argomenti della chiamata.
 *
 * Il solo tipo di ritorno non è sufficiente
 * per distinguere due overload.
 */

// Overload con double

double somma(double a, double b) {
    return a + b;
}


// ==================================================
// RICORSIONE
// ==================================================

/*
 * Una funzione ricorsiva richiama sé stessa.
 *
 * Deve prevedere:
 *
 * 1. Un caso base che interrompe la ricorsione.
 * 2. Un passo ricorsivo che avvicina al caso base.
 *
 * Esempio:
 *
 * S(n) = n + S(n-1)
 *
 * S(0) = 0
 *
 * Dominio previsto: n >= 0.
 */

int somma_dei_primi_n_numeri(int n) {

    if (n <= 0) {
        return 0;
    }

    return n + somma_dei_primi_n_numeri(n - 1);
}


// ==================================================
// MAIN
// ==================================================

int main() {

    // Dichiarazione e definizione

    std::cout << somma(5, 3) << '\n';


    // Funzione void

    print_hello_my_name("Luca");


    // Funzione con valore di ritorno

    int massimo = max_of_two(10, 20);

    std::cout << massimo << '\n';


    // Passaggio per valore

    int numero = 10;

    incrementa_valore(numero);

    std::cout << numero << '\n'; // 10


    // Passaggio per reference

    incrementa_reference(numero);

    std::cout << numero << '\n'; // 11


    // Passaggio per const reference

    std::string nome = "Mario";

    stampa_nome(nome);


    // Parametri di default

    print_auguri("Mario");

    print_auguri("Mario", "Buon compleanno");


    // Function overloading

    std::cout << somma(2, 3) << '\n';

    std::cout << somma(2.5, 3.7) << '\n';


    // Ricorsione

    std::cout
        << somma_dei_primi_n_numeri(5)
        << '\n'; // 15


    return 0;
}