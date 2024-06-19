/*
 Implementare un programma parallelo per l’ambiente multicore con np unità processanti che impieghi la libreria OpenMP. 
 Il programma deve essere organizzato come segue:
    il core master generare una matrice di dimensione N×M. 
    Quindi, ogni core deve estrarre la riga della matrice con indice uguale al proprio identificativo e conservarla in un vettore locale;
    successivamente deve sommare gli elementi di tale vettore e conservare il risultato in un vettore c di dimensione np. 
    Infine, i core devo collaborare per individuare in massimo tra gli elementi del vettore c.
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

    ///dichiarazione, allocazione e riempimento matrice
    double **a;
    allocationMatrixDouble(&a, N, M);
    fillMatrixDouble(&a, N, M);
    
    // Stampa la matrice
    printMatrixDouble(a, N, M, "Matrice Iniziale");

    double *c = (double*)calloc(nthreads, sizeof(double));

    double *local; //vettore locale
    double t0 = omp_get_wtime();
    
    // Sezione parallela
    #pragma omp parallel private(local) shared(a, c) num_threads(nthreads)
    {
        if (omp_get_thread_num() < N) {
            // Allocazione del vettore locale per ogni thread
            local = (double *)calloc(M, sizeof(double));
            double sum = 0.0;

            // Copia della riga con indice uguale al proprio identificativo
            for (int j = 0; j < M; j++) {
                local[j] = a[omp_get_thread_num()][j];
                sum += local[j];
            }

            // Salva la somma degli elementi del vettore locale in c[id]
            c[omp_get_thread_num()] = sum;

            // Stampa del vettore locale
            printf("Thread %d, local: ", omp_get_thread_num());
            for (int j = 0; j < M; j++) {
                printf("%lf ", local[j]);
            }
            printf("\n");

            // Stampa della somma
            printf("Thread %d, sum: %lf\n", omp_get_thread_num(), sum);

            // Deallocazione del vettore locale
            free(local);
        }
    }

    double t1 = omp_get_wtime();

    for (int i = 0; i < nthreads; i++) {
        printf("b[%d] = %lf\n", i, c[i]);
    }

    int max = c[0];

    #pragma omp parallel for shared(c, nthreads) num_threads(nthreads) reduction(max:max)
    for(int i = 0; i < nthreads; i++){
        if(max < c[i]){
            max = c[i];
        }
    }

    printf("max del vettore c = %d", max);

    //deallocazione della matrice
    deallocationMatrixDouble(&a, N);

    //deallocazione del vettore
    free(c);

    return 0;
}