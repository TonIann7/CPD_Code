/*Prova di utilizzo della libreria openmp*/
#include <omp.h>
#include <stdio.h>
int main(){

    int id_thread; //variabile per memorizzare l'id del thread
    int n_thread; //variabile per memorizzare il numero di thread

    //direttiva per il calcolo parallelo impostando le variabili private (private) e condivise(shared) tra i threads
    #pragma omp parallel private(id_thread), shared(n_thread)
    {
        id_thread = omp_get_thread_num(); // funzione che restituisce id di ciascun thread
        n_thread = omp_get_num_threads(); // funzione che restituisce il numero complessivo dei threads
        printf("Hello from thread %d, nthread %d\n", id_thread, n_thread); // stampa id di ogni thread e il numero di threads
    }
    return 0;
}

/* Nel terminale impostare export OMP_NUM_THREADS=2 per verificare cosa succede*/