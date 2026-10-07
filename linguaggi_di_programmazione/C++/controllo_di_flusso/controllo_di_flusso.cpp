#include <iostream>

/*
 * CONTROLLO DEL FLUSSO
 *
 * Le strutture di controllo permettono di modificare il normale
 * flusso sequenziale di esecuzione di un programma.
 *
 * Principali costrutti:
 * - if / else
 * - switch
 * - while
 * - do-while
 * - for
 * - range-based for
 * - break / continue
 *
 * I cicli for e while possono generalmente esprimere le stesse
 * strutture iterative.
 *
 * Il for è particolarmente adatto quando inizializzazione,
 * condizione e aggiornamento fanno naturalmente parte del ciclo.
 *
 * Il while è particolarmente adatto quando l'iterazione dipende
 * principalmente da una condizione.
 */

int main() {

    int x = 5;
    int y = 10;

    // ==================================================
    // IF / ELSE
    // ==================================================

    /*
     * if valuta una condizione.
     *
     * Se la condizione è true viene eseguito il relativo blocco.
     * È possibile concatenare più condizioni attraverso else if
     * e definire un caso alternativo tramite else.
     */

    if (x == 5) {
        std::cout << "x vale " << x << '\n';
    }

    if (x == 6) {
        std::cout << "Questo messaggio non viene stampato\n";
    }

    if (y < 10) {
        std::cout << "y è minore di 10\n";
    }
    else if (y == x) {
        std::cout << "y è uguale a x\n";
    }
    else if (y > 1000) {
        std::cout << "y è maggiore di 1000\n";
    }
    else {
        std::cout << "Nessuna delle condizioni precedenti è vera\n";
    }


    // ==================================================
    // SWITCH
    // ==================================================

    /*
     * switch permette di selezionare un ramo di esecuzione
     * in base al valore di un'espressione.
     *
     * I case devono utilizzare valori costanti compatibili
     * con il tipo utilizzato dallo switch.
     *
     * switch viene normalmente utilizzato con tipi integrali
     * ed enumerazioni.
     *
     * break interrompe l'esecuzione dello switch.
     *
     * Senza break l'esecuzione prosegue nei case successivi:
     * questo comportamento prende il nome di "fallthrough".
     *
     * default viene eseguito quando nessun case corrisponde.
     */

    int giorno = 2;

    switch (giorno) {

        case 1:
            std::cout << "Oggi è Domenica\n";
            break;

        case 2:
            std::cout << "Oggi è Lunedi\n";
            break;

        case 3:
            std::cout << "Oggi è Martedi\n";
            break;

        default:
            std::cout << "Giorno non valido\n";
            break;
    }


    // Esempio di fallthrough

    int valore = 2;

    switch (valore) {

        case 1:
            std::cout << "Uno\n";
            break;

        case 2:
            std::cout << "Due\n";
            // Nessun break: continua nel case successivo

        case 3:
            std::cout << "Tre\n";
            break;

        default:
            break;
    }


    // ==================================================
    // WHILE
    // ==================================================

    /*
     * while continua a eseguire il proprio blocco finché
     * la condizione rimane true.
     *
     * La condizione viene verificata PRIMA di ogni iterazione.
     *
     * Di conseguenza il corpo potrebbe anche non essere
     * mai eseguito.
     */

    int j = 0;

    while (j < 5) {

        std::cout << "Iterazione while n: " << j << '\n';

        j++;
    }


    // ==================================================
    // DO-WHILE
    // ==================================================

    /*
     * do-while è simile a while, ma la condizione viene
     * controllata DOPO l'esecuzione del corpo.
     *
     * Il corpo viene quindi eseguito almeno una volta.
     */

    int input;

    do {

        std::cout << "Inserisci un valore non negativo: ";
        std::cin >> input;

    } while (input < 0);

    std::cout << "Il valore inserito è: " << input << '\n';


    // ==================================================
    // FOR
    // ==================================================

    /*
     * Struttura:
     *
     * for (inizializzazione; condizione; aggiornamento) {
     *     ...
     * }
     *
     * È particolarmente utile quando la logica di controllo
     * dell'iterazione può essere espressa direttamente
     * nell'intestazione del ciclo.
     */

    for (int i = 0; i < 10; i++) {

        std::cout << "i: " << i << '\n';
    }


    /*
     * Le componenti del for possono essere omesse.
     *
     * Questo esempio si comporta come un while.
     */

    int k = 0;

    for (; k < 5;) {

        std::cout << "k vale: " << k << '\n';

        k++;
    }


    /*
     * È possibile anche creare intenzionalmente
     * un ciclo infinito:
     *
     * for (;;) {
     *     ...
     * }
     */


    // ==================================================
    // BREAK / CONTINUE
    // ==================================================

    /*
     * break
     * -----
     * Termina immediatamente il ciclo.
     *
     * continue
     * --------
     * Interrompe solamente l'iterazione corrente
     * e passa alla successiva.
     */

    for (int i = 0; i < 10; i++) {

        if (i == 3) {
            continue;
        }

        if (i == 7) {
            break;
        }

        std::cout << i << ' ';
    }

    std::cout << '\n';

    // Output:
    // 0 1 2 4 5 6


    // ==================================================
    // RANGE-BASED FOR
    // ==================================================

    /*
     * Il range-based for permette di iterare direttamente
     * sugli elementi di un insieme compatibile.
     *
     * In questo caso "val" assume, ad ogni iterazione,
     * il valore dell'elemento corrente dell'array.
     *
     * Reference e const reference verranno approfondite
     * successivamente.
     */

    int numeri[5] = {3, -5, 4, 3, 6};

    for (int val : numeri) {

        std::cout << val << ' ';
    }

    std::cout << '\n';


    // ==================================================
    // SCOPE
    // ==================================================

    /*
     * Lo scope determina la regione del programma
     * nella quale un identificatore è visibile.
     *
     * Un blocco delimitato da { } introduce un block scope.
     *
     * Una variabile dichiarata all'interno del blocco
     * non è accessibile dall'esterno.
     */

    int esterna = 10;

    if (esterna > 5) {

        int interna = 20;

        // Entrambe sono visibili
        std::cout << esterna << '\n';
        std::cout << interna << '\n';
    }

    // esterna è ancora visibile
    std::cout << esterna << '\n';

    // ERRORE:
    // std::cout << interna;
    //
    // "interna" appartiene allo scope del blocco if.


    /*
     * Lo stesso principio vale per la variabile
     * dichiarata nell'inizializzazione di un for.
     */

    for (int i = 0; i < 3; i++) {
        std::cout << i << '\n';
    }

    // ERRORE:
    // std::cout << i;
    //
    // i non è più visibile fuori dal for.


    return 0;
}