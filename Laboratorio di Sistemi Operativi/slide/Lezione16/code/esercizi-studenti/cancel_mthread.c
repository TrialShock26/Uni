#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void* funzione_lavoratore(void* arg) {
    long thread_id = (long)arg;
    printf("Lavoratore %ld: Avviato.\n", thread_id);

    for (int i = 0; i < 8; i++) {
        printf("Lavoratore %ld: sono vivo \t (secondo %d)\n", thread_id, i);
        sleep(1);
    }

    printf("Lavoratore %ld: Ho finito, sto terminando.\n", thread_id);
    pthread_exit(NULL);
}


void* funzione_killer(void* arg) {
    // L'id del thread del main viene passato come argomento
    pthread_t main_thread_id = (pthread_t)arg;

    printf("Killer: Avviato. Aspetto 3 secondi prima di colpire\n");
    sleep(3); // Diamo il tempo ai lavoratori di avviarsi e aspetta 3 sec

    printf("\nKiller: Cancello il main (id: %lu)!\n\n", (unsigned long)main_thread_id);
    

    // Invia la richiesta di cancellazione al thread main
    int result = pthread_cancel(main_thread_id);
    if (result != 0) {
    // Qui stampa sullo stderr se ci sono errori
        fprintf(stderr, "Killer: Errore nella cancellazione del thread main!\n");
    }
    
    printf("Killer: Richiesta inviata. Sto terminando.\n");
    pthread_exit(NULL);
}

int main() {
    // Il main thread ottiene il proprio id
    pthread_t main_thread_id = pthread_self(); 
    
    pthread_t lavoratore1, lavoratore2, killer_thread;
    long id1 = 1;
    long id2 = 2;

    // Attiva lo stato di cancellabilita' del main thread
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    printf("Main (%ld): Avviato. Creerò 2 lavoratori e 1 killer.\n", (long)main_thread_id);

    // Creiamo i thread lavoratori
    pthread_create(&lavoratore1, NULL, funzione_lavoratore, (void*)id1);
    pthread_create(&lavoratore2, NULL, funzione_lavoratore, (void*)id2);

    // Creiamo il thread killer, passandogli l'ID del main
    pthread_create(&killer_thread, NULL, funzione_killer, (void*)main_thread_id);

    // Il thread main si mette in un loop infinito
    printf("Main (%ld): Entro in un loop infinito in attesa di essere cancellato.\n", (long)main_thread_id);
    int count=0;
    while(1) {
	printf("Sono il Main e sono ancora vivo\t (secondo %d) \n", count++);
	sleep(1);
	//sleep e' un cancellation point
       // pthread_testcancel(); 
    }

    /*
     * Questo codice non dovrebbe mai venire raggiunto, perché il thread
     * viene terminato da pthread_cancel() del killer
     */
    printf("Main (%ld): Se vedi questo, la cancellazione non ha funzionato.\n", (long)main_thread_id);
    return 0;
}
