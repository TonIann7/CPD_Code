/*
 Implementare un programma parallelo per l’ambiente multicore con np unità processanti che impieghi la libreria OpenMP. 
 Il programma deve essere organizzato come segue: 
    il core master deve leggere una matrice A di dimensione N×N ed uno scalare alpha.
    Quindi, i core devono collaborare per calcolare il prodotto tra lo scalare alpha e la matrice A, sfruttano una strategia 
    di parallelizzazione che usi la distribuzione per colonne della matrice A come decomposizione del dominio.
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

    //dichiarazione, allocazione e riempimento matrice
    double **a;
    allocationMatrixDouble(&a, N, N);
    fillMatrixDouble(&a, N, N);

    double t0 = omp_get_wtime();
    #pragma omp parallel for shared(a, alpha, N)
    for(int i = 0; i < N; i++){ //calcolo prodotto scalare
        for(int j = 0; j < N; j++){
            a[i][j] *= alpha;
        }
    }
    double t1 = omp_get_wtime();

    //stampa
    printf("Il tempo di esecuzione è di: [%.6lfs]\n", t1 - t0);
    
    printMatrixDouble(a, N, N, "");
    
    deallocationMatrixDouble(&a, N);

    return 0;
}