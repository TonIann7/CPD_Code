/*
 Implementare un programma parallelo per l’ambiente multicore con np unità processanti che impieghi la libreria OpenMP. 
 Il programma deve essere organizzato come segue: 
    il core master deve generare una matrice A di dimensione N×M.
    Quindi, i core devono collaborare per calcolare il minimo tra gli elementi delle colonne di propria competenza e
    conservare tale valore in un vettore c di dimensione M.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include "src/allocazione.h"

int main(){
    int N, M; //dimensione problema
    int nthreads; //numero di threads da utilizzare

    //Inserimento dimensione problema
    printf("Inserisci n\n");
    scanf("%d", &N);

    printf("Inserisci M\n");
    scanf("%d", &M);

    //Inserimento numero di threadss
    printf("Inserisci numero threads\n");
    scanf("%d", &nthreads);

    //dichiarazione, allocazione e riempimento matrice
    double **a;
    allocationMatrixDouble(&a, N, M);
    fillMatrixDouble(&a, N, M);
    
    // Stampa la matrice
    printMatrixDouble(a, N, M, "Matrice Iniziale");

    //dichiarazione e allocazione vettore c
    double *c = (double*)malloc(N * sizeof(double));
    
    double t0 = omp_get_wtime();
    #pragma omp parallel for shared(a, c, N, M) num_threads(nthreads)
    for(int i = 0; i < N; i++){
        c[i] = a[i][0];

        for(int j = 0; j < M; j++){
            if(c[i] > a[i][j]){
                c[i] = a[i][j];
            }
        }
    }

    double t1 = omp_get_wtime();

    //stampa
    printf("Tempo eseguito per il calcolo [%.16lf] \n", t1 - t0);
    for (int i = 0; i < N; i++) {
        printf("c[%d] = %lf\n", i, c[i]);
    }

    //deallocazione
    deallocationMatrixDouble(&a, N);
    free(c);

    return 0;
}