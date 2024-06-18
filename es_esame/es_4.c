/*
 Implementare un programma parallelo per l’ambiente multicore con np unità processanti impieghi la libreria OpenMP. 
 Il programma deve essere organizzato come segue: 
    il core master deve leggere una matrice di dimensione N×N, quindi i core devo collaborare per ricopiare in parallelo gli 
    elementi della diagonale principale in un vettore di lunghezza N. 
    Infine, i core devono effettuare la somma degli elementi di tale vettore in parallelo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(){
    int N; //dimensione problema
    int nthreads; //numero di threads da utilizzare

    //Inserimento dimensione problema
    printf("Inserisci n\n");
    scanf("%d", &N);

    //Inserimento numero di threadss
    printf("Inserisci numero threads\n");
    scanf("%d", &nthreads);

    //Dichiarazione e allocazione matrice a e vettore b
    double *a = (double*)malloc((N * N) * sizeof(double));
    double *b = (double*)malloc(N * sizeof(double));

    //Riempimento matrice a
    printf("Inserisci elementi della matrice a\n");
    for (int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            scanf("%lf", &a[(i * N) + j]);
        }
    }

    double t0 = omp_get_wtime(); //calcolo tempo di esecuzione
    #pragma omp parallel for shared(a, b, N) num_threads(nthreads)
    for(int i = 0; i < N; i++){ //inserimento elementi diagonale della matrice nel vettore b
        b[i] = a[(i * N) + i];
    }

    double t1 = omp_get_wtime();

    double somma = 0; //dichiarazione variabile per la somma degli elementi del vettore b

    double t2 = omp_get_wtime();
    #pragma omp parallel for shared(b, N) reduction(+:somma)
    for (int i = 0; i < N; i++){ //calcolo somma elementi vettore b
        somma += b[i];
    }
    
    double t3 = omp_get_wtime();

    //stampa della somma
    printf("la somma vale: %lf\n", somma);

    //stampa tempo totale di esecuzione
    printf("Il tempo di esecuzione impiegato è di: %lfs", (t1 - t0) + (t3 - t2));
    return 0;
}