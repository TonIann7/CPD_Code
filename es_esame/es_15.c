/*
 Implementare un programma parallelo per l’ambiente multicore con np unità processanti che impieghi la libreria OpenMP.
 Il programma deve essere organizzato come segue:
    il core master deve leggere un vettore a, di dimensione M, e uno scalare alpha. 
    Quindi i core devono collaborare per costruire una matrice A, di dimensione M×M, la cui diagonale principale ha per
    elementi quelli del vettore a moltiplicati per lo scalare alpha.
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

    //Inserimento di alpha
    printf("Inserimento di alpha\n");
    scanf("%lf", &alpha);

    //dichiarazione e allocazione dei vettori
    double *b = (double*)malloc(N * sizeof(double));

    //dichiarazione e allocazione matrice
    double **a;
    allocationMatrixDouble(&a, N, N);

    srand(time(NULL));

    //riempimento vettori in modo casuale
    for (int i = 0; i < N; i++){
        b[i] = rand() % 9 + 1;
    }

    double t0 = omp_get_wtime();
    #pragma omp parallel for shared(a, b, N) num_threads(nthreads)
    for (int i = 0; i < N; i++){
        a[i][i] = b[i] * alpha;
    }

    double t1 = omp_get_wtime();

    //stampa
    printf("Il tempo di esecuzione è di: [%.6lfs]\n", t1 - t0);

    for (int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("mat[%d][%d] = %lf\n", i, j, a[i][j]);
        }
    }

    //deallocazione
    deallocationMatrixDouble(&a, N);

    free(b);

    return 0;
}