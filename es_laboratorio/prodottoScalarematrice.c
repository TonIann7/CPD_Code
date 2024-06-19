/*Prodotto di uno scalare con una matrice di grandi dimensioni!*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(){
    int N, nthreads, i, j; //Variabile dimensione del problema, numero di threads da utilizzare e contatori
    float b; //variabile B per il prodotto scalare
    
    printf("Inserisci n\n"); //Inserimento dimensione del problema
    scanf("%d", &N);

    printf("Inserisci nthreads\n"); //Inserimento numero di threads
    scanf("%d", &nthreads);

    float **a = (float**)calloc(N, sizeof(float)); //dichiarazione e allocazione della matrice a
    for (i = 0; i < N; i++) {
        a[i] = (float*)calloc(N, sizeof(float));
    }

    printf("Riempi la matrice a\n"); //Riempimento della matrice a
    for (i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            scanf("%f", &a[i][j]);
        }
    }

    printf("Inserisci b\n"); //Inserimento di b
    scanf("%f", &b);

    float **c = (float**)calloc(N, sizeof(float));
    for (i = 0; i < N; i++) {
        c[i] = (float*)calloc(N, sizeof(float));
    }

    double t0 = omp_get_wtime();
    #pragma omp parallel for shared(a, b, c, N) private(i,j) num_threads(nthreads)
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            c[i][j] = a[i][j] * b;
        }
    }

    /*
        Decomposizione per blocchi
        #pragma omp parallel for collapse(2)
        for(int blockRow = 0; blockRow < N; blockRow += blockSize){
            for(int blockCol = 0; blockCol < N; blockCol += blockSize){
                for(int i = blockRow; i < blockRow + blockSize && i < N; i++){
                    for (int j = blockCol; j < blockCol + blockSize && j < N; j++){
                        c[i][j] = a[i][j] * b;
                    }
                }
            }
        }
    */

    double t1 = omp_get_wtime();

     for (i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            printf("%f ", c[i][j]);
        }
        printf("\n");
    }

    printf("Il tempo vale: %.4f\n", t1 - t0);

    return 0;
}