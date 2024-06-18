/* Somma tra vettori in modo parallelo con la libreria openmp */
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(){

    int i, N, nloc, r, step; //variabili contatore, numero di operazione divisino numero di threads
    // La variabile step consente ad ogni core di sapere di quali elementi si deve occupare, mentre r verifica se nloc è divisibile
    float sumtot = 0, sum, *a; // variabili per calcolare la somma

    printf("Inserire N\n");
    scanf("%d", &N); // inserimento di n

    a = (float*)calloc(N, sizeof(float)); // creazione di un vettore dinamico di dimensione n

    printf("Inserire i numeri da sommare\n");

    for(i = 0; i < N; i++){ //riempimento del vettore 
        scanf("%f",&a[i]);
    }
    
    double t0 = omp_get_wtime(); //calcolo il tempo di inizio del pragma (quanto tempo ci mette a fare queste operazioni in parallelo)
    #pragma omp parallel private(sum, nloc, i) shared(sumtot) //inizio calcolo della somma in parallelo
    {
        nloc = N / omp_get_num_threads(); //numero di operazioni da effettuare in base al numero di thread;
        r = N % omp_get_num_threads(); // calcolo del resto della divisione di prima (verifica se il numero è divisibile oppure no)

        printf("sono %d, di %d: numeri %d, r=%d\n", omp_get_thread_num(), omp_get_num_threads(), nloc, r); // stampa di prova

        //Se il resto non è zero, tutti i processori con id strettamente minore del resto devono occuparsi di sommare un elemento in più:
        if(omp_get_thread_num() < r){
            nloc++; // incrementa nloc
            step = 0; // imposta step a 0
        }

        else
            step = r;

        printf("sono %d, di %d: numeri %d, r=%d, passo=%d\n", omp_get_thread_num(), omp_get_num_threads(), nloc, r, step); // stampa di prova

        sum = 0;
        for(i = 0; i < nloc; i++){
            sum += a[i + nloc * omp_get_thread_num() + step]; //calcolo della somma parziale
            //La variabile step consente ad ogni core di sapere di quali elementi si deve occupare.
        }

        printf("sono %d, di %d: numeri %d, r=%d, la mia sum=%f\n",omp_get_thread_num(), omp_get_num_threads(), nloc, r, sum); // stampa di prova

        sumtot += sum; // sommo la somma parziale alla somma totale
    }

    double t1 = omp_get_wtime();

    printf("Tempo totale: %.2f \n", t1 - t0);

    printf("somma totale: %f \n", sumtot); //stampo la somma totale

    return 0;
}