/*Calcolo del pigreco in parallelo con la libreria openmp utilizzando le direttive for, reduction o critical*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 100000000

int main(int argc, char** argv){

    long int i, n = N; //dichiarazione del contatore e n operazioni da svolgere
    double x, dx, f, sum = 0.0, pi; // //variabili per calcolare la formula del pigreco
    
    printf("numero di intervalli: %d\n", n); //stampa del numero di intervalli

    dx = 1.0 / (double) n; // cast di n da int a double e 1.0 viene diviso per n, come nella formula

    //costrutto con la direttiva for per dividere il lavoro tra i threads automaticamente
    //reduction specifica che la variabile sum deve essere trattata come una variabile di riduzione con l'operazione +.
    #pragma omp parallel for private(x, f, i) shared(dx, n) reduction(+:sum)
        for(i = 1; i <= n; i++){ //for per calcolare la sommatoria
            x = dx * ((double)(i-0.5)); //calcolo di x
            f = 4.0 / (1.0 + x * x); //calcolo di f

            /* Il costrutto critical forza l’esecuzione del blocco successivo ad un thread alla volta (come farlo in sequenziale): 
            è utile per gestire le regioni critiche */
            //#pragma omp critical
            sum += f; // calcolo della somma
        }

    pi = dx * sum; // calcolo del pigreco

    printf("PI %.24f\n", pi);

    return 0;
}