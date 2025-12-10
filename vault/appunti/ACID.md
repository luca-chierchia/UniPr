#ACID è l'acronimo di *Atomicity, Consistensy, Isolation, Durability* ( atomicità, consistenza, isolamento, durabilità):

-  **Atomicità**: l'atomicità rappresenta il fatto che la transazione è un unità indivisibile di esecuzione con l'approccio o tutto o niente, ovvero per essere portato a termine il *commit* (successo) della transazione ogni operazione prevista dalla transazione deve essere portato a termine con successo, pena l' *abort* (aborto) della transazione.

- **Consistenza**: la proprietà di consistenza garantisce che l'esecuzione di una transazione non violi i vincoli di integrità della base di dati, la verifica dei vincoli può essere di tipo:
 - immediato:  tipo di verifica che interrompe immediatamente la transazione.
 - differito: tipo di verifica che interrompe la transazione solo al termine di tutte le operazioni in fase di ***commit work*** , ciò permette temporaneamente alla transazione di violare i vincoli di integrità.

- **Isolamento**: l'isolamento deve garantire l'esecuzione contemporanea di più transazioni e che siano tutte indipendenti l'una dall'altra, inoltre se una transazione viene abortita non deve causare un effetto domino sulle altre transazioni in esecuzione, cioè ogni transazione è slegata da un altra.

- **Durabilità/Persistenza**: questa proprietà garantisce che al termine di ogni transazione i dati sono salvati correttamente e sono permanenti.
  Il #DBMS infatti assicura:
	 - scrittura sul disco
	 - meccanismi di [[recovery-dbms]]
	 - [[log-delle-transazioni]]



