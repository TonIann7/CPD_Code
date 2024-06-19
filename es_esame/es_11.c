/*
 Implementare un programma parallelo per l’ambiente multicore con np×np unità processanti che impieghi la libreria OpenMP. 
 Il programma deve essere organizzato come segue: 
 il core master deve generare una matrice A di dimensione N×N. 
 Quindi, ogni core deve sommare tra loro gli elementi di un blocco quadrato della matrice A di dimensione (N/np) × (N/np),
 conservando i valori in un vettore b.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include "src/allocazione.h"

int main(){
    int N; //dimensione problema
    int nthreads; //numero di threads da utilizzare

    //Inserimento dimensione problema
    printf("Inserisci n\n");
    scanf("%d", &N);


    //Inserimento numero di threadss
    printf("Inserisci numero threads\n");
    scanf("%d", &nthreads);

    //dichiarazione, allocazione e riempimento matrice
    double **a;
    allocationMatrixDouble(&a, N, N);
    fillMatrixDouble(&a, N, N);
    
    // Stampa la matrice
    printMatrixDouble(a, N, N, "Matrice Iniziale");

    //dichiarazione e allocazione vettore c
    double *b = (double*)calloc(nthreads, sizeof(double));

    int blockSize = N/nthreads;

    double t0 = omp_get_wtime();
    #pragma omp parallel for shared(a, N) reduction(+:b[:nthreads]) num_threads(nthreads) collapse(2)
    for(int i = 0; i < N; i += blockSize){
        for(int j = 0; j < N; j += blockSize){
            for(int r = i; r < i + blockSize && r < N; r++){
                for(int c = j; c < j + blockSize && c < N; c++){
                    b[i/blockSize] += a[r][c];
                }
            }
        }
    }
    double t1 = omp_get_wtime();

    //stampa
    printf("Tempo eseguito per il calcolo [%.16lf] \n", t1 - t0);
    for (int i = 0; i < N; i++) {
        printf("b[%d] = %lf\n", i, b[i]);
    }

    //deallocazione della matrice
    deallocationMatrixDouble(&a, N);

    //deallocazione del vettore
    free(b);

    return 0;
}