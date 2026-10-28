#include <iostream>
#include <string>

// Scrivere un programma che legga e scriva l'informazione di 100 clienti di una determinata impresa.
// I clienti hanno un nome, il numero di unità ordinate, il prezzo di ogni unità
// e lo stato in cui si trova: moroso, in ritardo, pagato

enum statoPagamento {
    MOROSO,
    IN_RITARDO,
    PAGATO
};

struct Cliente {
    std::string nome;
    int quantitaOrdinata;
    float prezzoUnita;
    statoPagamento stato;
};

void fatturaMoroso(const Cliente& c, float f) {
    if (c.stato == MOROSO) {
        float totaleFattura = c.prezzoUnita * c.quantitaOrdinata;
        if (totaleFattura < f) {
            std::cout << c.nome << " deve saldare "
                      << totaleFattura << "\n";
        }
    }
}

void fatturaPagata(const Cliente& c, float f) {
    if (c.stato == PAGATO) {
        float totaleFattura = c.prezzoUnita * c.quantitaOrdinata;
        if (totaleFattura > f) {
            std::cout << c.nome << " fattura con importo: "
                      << totaleFattura << "\n";
        }
    }
}

#define DEBUG_ON


int main() {
#ifdef DEBUG_ON
    // Modalità debug: 10 clienti precaricati
    Cliente clienti[100] = {
        {"Rossi",    10, 25.5f,  MOROSO},
        {"Bianchi",   5, 100.0f, PAGATO},
        {"Verdi",    20, 12.75f, IN_RITARDO},
        {"Neri",      8, 50.0f,  MOROSO},
        {"Gallo",    15, 30.0f,  PAGATO},
        {"Conti",     3, 200.0f, MOROSO},
        {"Esposito", 12, 45.5f,  PAGATO},
        {"Ferrari",   7, 80.0f,  IN_RITARDO},
        {"Romano",   25, 10.0f,  MOROSO},
        {"Colombo",   6, 150.0f, PAGATO}
    };
    int i = 10;
#else
// Modalità normale: archivio vuoto
    Cliente clienti[100];
int i = 0;
#endif


    int selezione = 0;

    do {
        std::cout << "\nScegli un'operazione:\n"
                  << "1: Inserisci cliente\n"
                  << "2: Trova clienti morosi\n"
                  << "3: Trova fatture pagate dal valore maggiore di (>)\n"
                  << "4: Chiudi programma\n";

        std::cin >> selezione;

        switch (selezione) {

            case 1: {
                if (i >= 100) {
                    std::cout << "Archivio pieno!\n";
                    break;
                }

                std::cout << "Inserire nome\n";
                std::cin >> clienti[i].nome;

                std::cout << "Inserire quantita acquistata\n";
                std::cin >> clienti[i].quantitaOrdinata;

                std::cout << "Inserire prezzo del prodotto\n";
                std::cin >> clienti[i].prezzoUnita;

                int stato;

                std::cout << "Stato fattura (0=Moroso, 1=Ritardo, 2=Pagato)\n";
                std::cin >> stato;

                if (stato < 0 || stato > 2) {
                    std::cout << "Stato non valido\n";
                    break;
                }

                clienti[i].stato = static_cast<statoPagamento>(stato);

                i++;
                break;
            }

            case 2: {
                float val = 0;
                std::cout << "Inserire valore per cercare fatture di clienti MOROSI "
                          << "con fatture minori dell'importo inserito:\n";
                std::cin >> val;
                for (int j = 0; j < i; j++) {
                    fatturaMoroso(clienti[j], val);
                }
                break;
            }

            case 3: {
                float val = 0;
                std::cout << "Inserire valore per cercare fatture di clienti con stato "
                          << "PAGATO maggiori del valore inserito:\n";
                std::cin >> val;
                for (int j = 0; j < i; j++) {
                    fatturaPagata(clienti[j], val);
                }
                break;
            }

            case 4:
                std::cout << "Chiusura programma\n";
                break;

            default:
                std::cout << "Operazione non valida\n";
        }

    } while (selezione != 4);

    return 0;
}
