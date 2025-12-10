# Modellazione concettuale 

La progettazione di un database inizia prima della reale definizione delle tabelle, dei suoi attributi e delle sue relazioni interne ed esterne, della tipologia di dati e del loro dominio, prima di arrivare alla realizzazione pratica bisogna capire quali dati servono e come sono collegati tra loro.

In questo contesto interviene la **progettazione concettuale**, dove si definiscono tramite analisi i requisiti degli utenti (clienti). Questo processo comprende:

1. Raccolta dei requisiti.
2. Analisi dei requisiti.
3. Costruzione del glossario.
4. Identificazione delle entità, attributi, relazioni e generalizzazioni o specializzazioni.
5. Strategie di modellazione: top-down, bottom-up, inside-out, mista.

## Metodologia generale

1. **Analisi dei requisiti**.
   - (a) costruire un glossario dei termini. 
   - (b) analizzare i requisiti ed eliminare le ambiguità presenti. 
   - (c) raggruppare i requisiti in insiemi omogenei. 
1. **Passo base**.
   - (a) individuare i concetti più rilevanti e rappresentarli in uno schema scheletro.
1. **Passo di decomposizione**. (se necessario)
   - (a) effettuare una decomposizione dei requisiti con riferimento ai concetti presenti nello schema scheletro.
1. **Passo Iterativo**.
   - (a) raffinare i concetti presenti sulla base delle loro specifiche.
   - (b) aggiungere i nuovi concetti allo schema per descrivere le specifiche non ancora descritte.
1. **Passo di integrazione**. (se necessario)
   - (a) integrare i vari sottoschemi ottenuti con la decomposizioni.
1. **Analisi di qualità**.
   - (a) verifica della correttezza dello schema.
   - (b) verifica della completezza dello schema.
   - (c) verifica leggibilità dello schema
   - (d) integrazione di documentazione ove non è stato possibile specificare requisiti con lo schema grafico.


