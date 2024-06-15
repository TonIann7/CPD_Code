/*Assegnata una matrice di dimensione N×N, estrarre in parallelo gli elementi della diagonale principale e ricopiarli in un vettore, 
quindi calcolarne il massimo, con una procedura parallela*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h> 

int main(){

    int n; //dimensione del problema

    //inserimento dimensione del problema
    printf("Inserisci la dimensione della matrice quadrata: ");
    scanf("%d", &n);

    //dichiarazione e allocazione matrice a
    int **a = (int **)malloc(n * sizeof(int *));

    for(int i = 0; i < n; i++)
        a[i] = (int *)malloc(n * sizeof(int));
    
    //inserimento elementi nella matrice a
    printf("Inserisci gli elementi della matrice: \n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &a[i][j]);
        }
    }
    
    int *diag = (int *)malloc(n * sizeof(int)); //vettore per memorizzare diagonale della matrice a
    
    double t0 = omp_get_wtime(); //calcolo del tempo di esecuzione del primo pragma
    #pragma omp parallel for shared(a, diag, n)
    for(int i = 0; i < n;  i++){
        diag[i] = a[i][i]; //copia dei valori della diagonale
    }
    
    double t1 = omp_get_wtime(); //calcolo del tempo finito dell'esecuzione del primo pragma

    //stampa della diagonale principale di a
    printf("Diagonale principale:\n");
    for(int i = 0; i < n; i++){
        printf("%d\n", diag[i]);
    }

    int max = 0; //variabile per calcolare il massimo

    double t2 = omp_get_wtime(); //calcolo del tempo di esecuzione del secondo pragma
    #pragma omp parallel for shared(a, diag, n) reduction(max:max)
    
    //calcolo dell' elemento massimo della diagonale della matrice a con la collezione dei risultati di ogni threads
    for(int i = 0; i < n;  i++){
       if(max < diag[i]){ //verifico se il massimo attuale è più piccolo dell'elemento della diagonale
        max = diag[i]; //l'elemento della diagonale è il nuovo massimo
       }
    }

    double t3 = omp_get_wtime(); //calcolo del tempo finito dell'esecuzione del secondo pragma

    double tf = (t1 - t0) + (t3 - t2); //calcolo tempo totale di esecuzione dei pragma

    printf("max: %d\n", max); //stampa del massimo

    printf("I tempi sono: %f \n", tf);// stampa del tempo totale di esecuzione dei pragma

    return 0;
}