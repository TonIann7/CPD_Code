/*
 Implementazione di un algoritmo parallelo (np core) per il calcolo degli elementi di un vettore c, i cui valori sono ottenuti 
 moltiplicando l’identificativo del core per gli elementi di un vettore a di dimensione N, in ambiente openMP
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(){
    int N; //dimensione problema
    int nthreads; //numero di threads da utilizzare

    //Inserimento dimensione problema
    printf("Inserisci n\n");
    scanf("%d", &N);

    //Inserimento numero di threadss
    printf("Inserisci numero threads\n");
    scanf("%d", &nthreads);

    //dichiarazione e allocazione del vettori
    float *a = (float*)malloc(N * sizeof(float));

    //inserimento elementi vettori a
    printf("Inserisci elementi vettore a\n");
    for (int i = 0; i < N; i++){
        scanf("%f", &a[i]);
    }

    //dichiarazione e allocazione vettore c
    float *c = (float*)malloc(N * sizeof(float));

    double t0 = omp_get_wtime();
    #pragma parallel for shared(a, c, N) num_threads(nthreads)
    for(int i = 0; i < N; i++){
        c[i] = a[i] * omp_get_thread_num();
    }

    double t1 = omp_get_wtime();

    printf("Il tempo di esecuzione è %lfs \n", t1 - t0);

    for (int i = 0; i < N; i++){
        printf("%f\n", c[i]);
    }

    free(a);
    free(c);

    return 0;
}