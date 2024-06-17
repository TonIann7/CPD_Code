/*
 Implementare un programma parallelo per l’ambiente multicore con np unità processanti che impieghi la libreria OpenMP. 
 Il programma deve essere organizzato come segue:
    il core master deve generare una matrice B di dimensione NxN e due vettori a, b di lunghezza N
    i core devono collaborare per costruire, in parallelo, una nuova matrice A ottenuta sommando alla diagonale principale della 
    matrice B il vettore b
    quindi, i core devono collaborare per calcolare in parallelo il prodotto tra la nuova matrice A ed il vettore a, distribuendo 
    il lavoro per colonne
    infine, il core master stampa il risultato finale ed il tempo d’esecuzione
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
    int N; //dimensione del problema
    int nthreads; //numero di threads da utilizzare

    //Inserimento dimensione del problema
    printf("Inserisci N\n");
    scanf("%d", &N);

    //Inserimento numero di threads
    printf("Inserisci numero di threads da utilizzare\n");
    scanf("%d", &nthreads);

    //dichiarazione e allocazione matrice B
    double *B = (double*)malloc((N * N) * sizeof(double));

    //Riempimento matrice B
    printf("Inserisci elementi della matrice B\n");
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            scanf("%lf", &B[(i * N) + j]);
        }
    }

    //dichiarazione e allocazione vettori a e b
    double *a = (double*)malloc(N * sizeof(double));
    double *b = (double*)malloc(N * sizeof(double));

    //riempimento vettori a e b
    printf("Inserimento elementi dei vettori a e b\n");
    for(int i = 0; i < N; i++){
        scanf("%lf %lf", &a[i], &b[i]);
    }

    double t0 = omp_get_wtime(); //calcolo tempo di esecuzione
    #pragma omp parallel for shared(B,b) num_threads(nthreads)
    for(int i = 0; i < N; i++){ //somma in parallelo diagonale della matrice B con il vettore b
        B[(i * N) + i] += b[i];
    }

    double t1 = omp_get_wtime();

    //dichiarazione e allocazione array contenente il risultato
    double *result = (double*)malloc(N * sizeof(double));

    double t2 = omp_get_wtime();
    #pragma omp parallel for shared(B,a) reduction(+:result[:N]) num_threads(nthreads)
    for(int i = 0; i < N; i++){ //prodotto scalare tra il vettore a e la matrice B
        for(int j = 0; j < N; j++){
            // #pragma omp atomic
            result[j] += B[(i * N) + j] * a[j];
        }
    }

    double t3 = omp_get_wtime();

    //calcolo e stampa del tempo di esecuzione totale
    printf("Il tempo di esecuzione è: %lfs\n", (t1 - t0) + (t3 - t2));
    
    //stampa risultato
    for (int i = 0; i < N; i++){
        printf("%lf\n", result[i]);
    }
    
}