#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
    int i, N; // variabile contatore e dimensione massima
    float *a, *b, result; // dichiarazione di due vettori e memorizzazione risultato finale

    printf("Inserire N\n");
    scanf("%d", &N); // inserimento di N

    //allocazione dinamica dei vettori
    a = (float *)calloc(N, sizeof(float));
    b = (float *)calloc(N, sizeof(float));

    //lettura
    printf("Inserire gli elementi del vettore a\n");

    for(i = 0; i < N; i++){ // riempimento vettore a
        scanf("%f", &a[i]);
    }

    //lettura
    printf("Inserire gli elementi del vettore b\n");

    for(i = 0; i < N; i++){ // riempimento vettore b
        scanf("%f", &b[i]);
    }

    // direttiva nella vesione più semplice possibile
    #pragma omp parallel for private(i) shared(a, b) reduction(+:result)
        for (i = 0; i < N; i++){
            result += (a[i] * b[i]); //calcolo prodotto scalare
        }
    
    //stampa del risultato
    printf("\n Risultato = %f\n", result);

    //libero la memoria
    free(a);
    free(b);
        
}