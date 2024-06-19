/*
 Implementare un programma parallelo per l’ambiente multicore con np unità processanti che impieghi la libreria OpenMP. 
 Il programma deve essere organizzato come segue: 
    il core master deve leggere una matrice di dimensione N×M, 
    quindi i core devo collaborare per sommare in parallelo i vettori corrispondenti alle righe dispari della matrice.
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
    double *b = (double*)calloc(N, sizeof(double));
    
    //variabile somma
    double somma = 0;

    double t0 = omp_get_wtime();
    #pragma omp parallel for shared(a, N, M) num_threads(nthreads)
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(i % 2 != 0){
                #pragma omp atomic
                b[j] += a[i][j]; 
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