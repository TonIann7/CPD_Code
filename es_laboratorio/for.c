/*Esempio di utilizzo della direttiva for con la libreria openmp*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>
#define N 1000
#define CHUNK 10

int main( ){
    
    int n_threads, i;
    
    // omp_set_num_threads(3); imposto il numero di threads massimi da utilizzare

    double t0 = omp_get_wtime();
    //num_threads imposto il numero di threads massimi da utilizzare per la direttiva specifica.
    // schedule(dinamic) o schedule(dinamic, CHUNK)
    //In questo modo ciascun thread ha una iterazione: quando questo termina gli verrà assegnata la successiva iterazione.
    /*E’ possibile migliorare le prestazioni utilizzando l’opzione chunk con la modalità dynamic.
      In questo modo, ad ogni thread sarà associato un numero prestabilito di iterazioni, quindi quando avrà terminato avrà assegnato 
      un nuovo chunk.*/
    /*La modalità guided ha una politica di pianificazione molto simile alla modalità dynamic, tranne per il fatto che la dimensione 
      del chunk cambia durante l'esecuzione del programma*/

    #pragma omp parallel for private(i) schedule(guided) num_threads(4)
    for (i=0; i<N; i++){
        printf("Il thread %d ha completato iterazione %d.\n", omp_get_thread_num(), i);
    }

    double t1 = omp_get_wtime();
    
    printf("Tutti I thread hanno terminato!\n");

    printf("Tempo totale: %.4f\n", t1 - t0);

    return 0;
}