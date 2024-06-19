/*
 Implementare un programma parallelo per l’ambiente multicore con np unità processanti che impieghi la libreria OpenMP. 
 Il programma deve essere organizzato come segue: 
    il core master generare una matrice A di dimensione M×M. 
    Quindi, i core devo collaborare valutare il minimo valore tra gli elementi di A e successivamente costruire la matrice B i cui
    elementi sono dati dalla somma di tale valore minimo per gli elementi di posto corrispondente della matrice di partenza.
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
    
    //allocazione matrice b
    double **b;
    allocationMatrixDouble(&b, N, N);

    double min = a[0][0]; //variabile per trovare il minimo

    double t0 = omp_get_wtime();
    #pragma omp paraller for shared(a, N) reduction(min:min) num_threads(nthreads)
    for(int i = 0; i < N; i++){ //ricerca del minimo
        for(int j = 0; j < N; j++){
            if(min > a[i][j]){
                min = a[i][j];
            }
        }
    }
    double t1 = omp_get_wtime();

    printf("min: %d\n", min);

    double t2 = omp_get_wtime();
    #pragma omp parallel for shared(a, b, min) num_threads(nthreads)
    for(int i = 0; i < N; i++){ //somma elementi della matrice con il minimo
        for(int j = 0; j < N; j++){
            b[i][j] = a[i][j] + min;
        }
    }

    double t3 = omp_get_wtime();

    //Stampa
    printMatrixDouble(b, N, N, "Matrice con somma minimo");

    printf("Tempo eseguito per il calcolo [%.16lf] \n", (t1 - t0) - (t3 - t2));

    //deallocazione delle matrice
    deallocationMatrixDouble(&a, N);
    deallocationMatrixDouble(&b, N);

    return 0;
}