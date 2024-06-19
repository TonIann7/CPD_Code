/*calcolo del prodotto di una matrice A per un vettore b*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(){
    int N, nthreads; //Variabile dimensione del problema, numero di threads da utilizzare e contatori
    
    printf("Inserisci n\n"); //Inserimento dimensione del problema
    scanf("%d", &N);

    printf("Inserisci nthreads\n"); //Inserimento numero di threads
    scanf("%d", &nthreads);

    float **a = (float**)calloc(N, sizeof(float)); //dichiarazione e allocazione della matrice a
    for (int i = 0; i < N; i++) {
        a[i] = (float*)calloc(N, sizeof(float));
    }
    
    printf("Riempi la matrice a\n"); //Riempimento della matrice a
    for (int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            scanf("%f", &a[i][j]);
        }
    }

    float *b = (float*)calloc(N, sizeof(float)); //dichiarazione e allocazione del vettore b

    printf("Riempi il vettore b\n"); //Riempimento del vettore b
    for (int i = 0; i < N; i++){
        scanf("%f", &b[i]);  
    }

    float *c = (float*)calloc(N, sizeof(float));

    double t0 = omp_get_wtime();
    #pragma omp parallel for shared(a, b, c, N) num_threads(nthreads)
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            c[i] += a[i][j] * b[i];
        }
    }

    /*
        Seconda strategia:
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                c[i] += a[j][i] * b[i];
            }
        }
    */

    double t1 = omp_get_wtime();

     for (int i = 0; i < N; i++){
        printf("%f ", c[i]);
    }

    printf("\nIl tempo vale: %.4f\n", t1 - t0);

    return 0;
}