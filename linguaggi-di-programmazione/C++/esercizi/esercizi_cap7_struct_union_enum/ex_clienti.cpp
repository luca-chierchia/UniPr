#include <iostream>
#include <string>
// Scrivere un programma che legga e scriva l'informazione di 100 clienti di una determianta impresa.
// I clienti hanno un nome, il numero di unità odrinate, il prezzo di ogni unità e lo stato in cui si trova: moroso, in ritardo, pagato
#include <iostream>
#include <string>

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

void fatturaMoroso(const Cliente& c) {
    if (c.stato == MOROSO) {
        float totaleFattura = c.prezzoUnita * c.quantitaOrdinata;
        std::cout << c.nome << " deve saldare "
                  << totaleFattura << "\n";
    }
}

int main() {
    Cliente clienti[100];

    int selezione = 0;
    int i = 0;

    do {
        std::cout << "\nScegli un'operazione:\n"
                  << "1: Inserisci cliente\n"
                  << "2: Trova clienti morosi\n"
                  << "3: Chiudi programma\n";

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

            case 2:
                for (int j = 0; j < i; j++) {
                    fatturaMoroso(clienti[j]);
                }
                break;

            case 3:
                std::cout << "Chiusura programma\n";
                break;

            default:
                std::cout << "Operazione non valida\n";
        }

    } while (selezione != 3);

    return 0;
}
