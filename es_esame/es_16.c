/*
 Implementare un programma parallelo per l’ambiente multicore con nq×np unità processanti che impieghi la libreria OpenMP. 
 Il programma deve essere organizzato come segue: 
    il core master deve costruire una matrice A, di dimensione M×N, i cui blocchi sono generati casualmente e in parallelo da ogni core.
*/


/*
Implementare un programma parallelo per l'ambiente multicore con nqxnp unità processanti
che impieghi la libreria OpenMP.
Il programma deve essere organizzato come segue:
1)Il core master deve costruire una matrice A di dimensione MxN..
2)II blocchi della matrice A sono generati casualmente e in parallelo da ogni core.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(){
    int N,M,q,p; // size del problema
    int nthreads; // numero di threads da utilizzare

    //Inserimento dimensione problema
    printf("Inserire il size del problema (M)(N):\n");
    scanf("%d %d", &M, &N);

    //Inserimento numero di core
    printf("Inserire il numero di core riga(q) e colonna(p)\n");
    scanf("%d %d", &q, &p);

    nthreads = q * p; // numero di threads da utilizzare

    //dichiarazione e allocazione matrice a
    double **A = (double**)calloc(M, sizeof(double*));
    for(int i = 0; i < M; i++){
        A[i] = (double*)calloc(N, sizeof(double));
    }


    int blockSize=N/q; //divisione dei blocchi della matrice
    srand(time(NULL)); //impostazione della casualità

    double t0=omp_get_wtime();
    #pragma omp parallel for collapse(2) shared(A) num_threads(nthreads)
    for (int blockRow = 0; blockRow < M; blockRow += blockSize) { // riempimento vettore in modo casuale
            for (int blockCol = 0; blockCol < N; blockCol += blockSize) {
                for (int i = blockRow; i < blockRow + blockSize && i < M; i++) {
                    for (int j = blockCol; j < blockCol + blockSize && j < N; j++) {
                        A[i][j]=rand()%10+1;
                    }
                }
            }
    }
    double t1=omp_get_wtime();
    
    //stampa
    printf("La matrice A ha i seguenti valori:\n");
    for(int i = 0;i < M; i++){
        for(int j=0;j<N;j++){
            printf("A[%d][%d]=%lf ",i,j,A[i][j]);
        }printf("\n");}

        printf("Il tempo impiegato è : %lf ",t1-t0);
        for(int i = 0;i<N;i++){
            free(A[i]);
    }
    free(A);

     return 0;
 }