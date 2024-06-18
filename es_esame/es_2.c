/*
 Implementazione di un algoritmo parallelo (np core) per il calcolo dell’operazione c=alpha*a+b, con a,b vettori di dimensione N e 
 alpha uno scalare, in ambiente openMP
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(){
    int N; //dimensione problema
    int nthreads; //numero di threads da utilizzare
    int alpha; //variabile per il prodotto scalare

    //Inserimento dimensione problema
    printf("Inserisci n\n");
    scanf("%d", &N);

    //Inserimento numero di threadss
    printf("Inserisci numero threads\n");
    scanf("%d", &nthreads);

    //Inserimento di alpha
    printf("Inserisci numero alpha\n");
    scanf("%d", &alpha);


    //dichiarazione e allocazione dei vettori
    float *a = (float*)malloc(N * sizeof(float));
    float *b = (float*)malloc(N * sizeof(float));

    //inserimento elementi vettori a e b
    printf("Inserisci elementi vettore a\n");
    for (int i = 0; i < N; i++){
        scanf("%f", &a[i]);
    }

    printf("Inserisci elementi vettore b\n");
    for (int i = 0; i < N; i++){
        scanf("%f", &b[i]);
    }

    //dichiarazione e allocazione vettore c
    float *c = (float*)malloc(N * sizeof(float));
    
    double t0 = omp_get_wtime();
    #pragma parallel for shared(a, b, c, N) num_threads(nthreads)
    for(int i = 0; i < N; i++){ //somma parallela
        c[i] = alpha * a[i] + b[i];
    }

    double t1 = omp_get_wtime();

    printf("Il tempo di esecuzione è %lfs \n", t1 - t0);

    for (int i = 0; i < N; i++){
        printf("%f\n", c[i]);
    }
    
}