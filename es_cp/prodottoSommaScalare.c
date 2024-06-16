/*Calcolo prodotto Scalare tra matrice A e il vettore b per alpha + beta per il vettore a*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>

int main(){
    int N, nthreads; //dimensione del problema, numero di threads da utilizzare
    int alpha, beta; //variabili alpha e beta per il calcolo del problema

    double p = 0.00f;

    printf("Inserisci N\n"); //Inserimento dimensione del problema
    scanf("%d", &N);

    printf("Inserisci numero di threads da utilizzare\n"); //Inserimento numero di threads da utilizzare
    scanf("%d", &nthreads);

    printf("Inserisci alpha\n"); //Inserimento di alpha
    scanf("%d", &alpha);

    printf("Inserisci beta\n"); //Inserimento di beta
    scanf("%d", &beta);

    //dichiarazione e allocazione matrice A
    double *A = (double*)malloc((N * N) * sizeof(double));

    //dichiarazione e allocazione vettore a
    double *a = (double*)malloc(N * sizeof(double));
    
    //Generazione numeri casuali per il riempimento della matrice A e del vettore a
    for (int i = 0; i < N; i++){
        a[i] = (double)((rand() % 1000) + 1) / 1000;

        for (int j = 0; j < N; j++){
            A[(i * N) + j] = (double)((rand() % 1000) + 1) / 1000;
        }
    }

    //dichiarazione e allocazione vettore b
    double *b = (double*)malloc(N * sizeof(double));

    //Generazione numeri casuali per il riempimento del vettore b
    for (int i = 0; i < N; i++){
        b[i] = (double)((rand() % 1000) + 1) / 1000;
    }
    
    //dichiarazione e allocazione matrice R
    double *R = (double*)malloc((N * N) * sizeof(double));

    int ops = 0; //contatore operazioni eseguite
    double t0 = omp_get_wtime(); //calcolo tempo di esecuzione inizio pragma
    #pragma omp parallel for schedule(static) shared(alpha, beta, A, a, b, N, R) num_threads(nthreads)
    for (int i = 0; i < N; i++){ //calcolo A · b + β · a;
        for(int j = 0; j < N; j++){
            R[i] += alpha * A[(i * N) + j] * b[j];

            #pragma omp critical //incrementa facendo attendere i threads il numero di operazioni
            {
                ops += 1;
            }
        }

        R[i] += (a[i] * beta);
    }

    #pragma omp parallel for shared(R, N, a) reduction(*:p) num_threads(nthreads)
    for (int i = 0; i < N; i++){ //ricavo il risultato di r
        p *= R[i];
    }
    
    double t1 = omp_get_wtime(); //calcolo tempo fine pragma

    printf("Tempo totale: %lfs \nOps = %d\n", t1 - t0, ops); //stampa del tempo

    free(A);
    free(a);
    free(b);
    free(R);

    return 0;
}