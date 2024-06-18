/*
 Implementare un programma parallelo per l’ambiente multicore con np unità processanti che impieghi la libreria OpenMP. 
 Il programma deve essere organizzato come segue: 
    il core master deve generare due vettori casuali di dimensione N. 
    Ogni core deve sommare ad ogni elemento dei due vettori il proprio identificativo e collaborare alla costruzione di una matrice, 
    di dimensione N×M, con M=2np, le cui colonne, a due a due, sono i due vettori ottenuti nella fase precedente.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include "src/allocazione.h"

int main(){
    int N; //dimensione problema
    int nthreads; //numero di threads da utilizzare
    double alpha; // variabile scalare

    //Inserimento dimensione problema
    printf("Inserisci n\n");
    scanf("%d", &N);

    //Inserimento numero di threadss
    printf("Inserisci numero threads\n");
    scanf("%d", &nthreads);

    //dichiarazione e allocazione dei vettori
    double *a = (double*)malloc(N * sizeof(double));
    double *b = (double*)malloc(N * sizeof(double));

    //riempimento vettori in modo casuale
    for (int i = 0; i < N; i++){
        a[i] = rand() % 9 + 1;
        b[i] = rand() % 9 + 1;
    }

    //dichiarazione e allocazione matrice
    double **mat;
    int M = 2 * nthreads;
    allocationMatrixDouble(&mat, N, M);
    
    double t0 = omp_get_wtime();
    #pragma omp parallel for shared(a, b, mat, N, M) num_threads(nthreads)
    for (int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(i % 2 == 0){
                mat[i][j] = a[j] + omp_get_thread_num(); 
            }
            else{
                mat[i][j] = b[j] + omp_get_thread_num();
            }
        }
    }

    double t1 = omp_get_wtime();

    //stampa
    printf("Il tempo di esecuzione è di: [%.6lfs]\n", t1 - t0);
    
    for (int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            printf("mat[%d][%d] = %lf\n", i, j, mat[i][j]);
        }
    }

    //deallocazione
    deallocationMatrixDouble(&mat, N);

    free(a);
    free(b);
    
    return 0;
}