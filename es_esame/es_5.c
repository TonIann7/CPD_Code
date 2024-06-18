/*
 Implementare un programma parallelo per l’ambiente multicore con np unità processanti che impieghi la libreria OpenMP. 
 Il programma deve essere organizzato come segue: 
    il core master deve generare una matrice di dimensione N×N, ogni core deve estrarre N/np righe e calcolare il prodotto puntuale tra i 
    vettori corrispondenti alle righe estratte.
*/

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <malloc.h>

int main(int argc, char **argv) {
    if (argc < 3) { //inserimento della dimensione N e numero di processori
        printf("Inserire N & np\n");
    }
    int N = atoi(argv[1]); // variabile dimensione del problema
    int np = atoi(argv[2]); // variabile numero di core utilizzabili
    int blockSize = N / np; // divisione del blocco
    int i, j, k, l; // variabili contatore
    printf("block size [%d]", blockSize); //stampa della divisione del blocco
    int **mat = (int **) calloc(N, sizeof(int *)); //dichiarazione e allocazione matrice
    int *vetB = (int *) calloc(N, sizeof(int)); //dichiarazione e allocazione vettore
    for (i = 0; i < N; i++) { // riempimento matrice
        mat[i] = (int *) calloc(N, sizeof(int));
        for (j = 0; j < N; j++) {
            mat[i][j] = 2;
        }
    }
    for (j = 0; j < N; j++) { //riempimento vettore b
        vetB[j] = 1;
    }
    double t0, t1; //variabili calcolo tempo
    t0 = omp_get_wtime();
#pragma omp parallel for private (i,j,k,l) shared(mat,N,np,blockSize) reduction(*:vetB[:N]) collapse(2)
    for(i=0;i<N;i++) { //calcolo prodotto puntuale
        for(j=0;j<N;j++) {
            vetB[i] *= mat[i][j];
        }
    }

    t1 = omp_get_wtime();
    
    //stampa
    printf("tempo per il calcolo [%.16lf] \n", t1 - t0);
    for (i = 0; i < N; i++) {
        printf("vetB[%d] = %d\n", i, vetB[i]);
    }
}