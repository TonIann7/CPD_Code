/* Somma tra vettori in modo parallelo con la libreria openmp*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int main(){
    int i; //indice per i cicli
    int N; //dimensione dei vettori
    int t; //numero di thread
    int nloc; //numero di elementi per thread
    int indice; //indice di partenza per ciascun thread
    int id; //id del thread
    int step; //variabile di appoggio, La variabile step consente ad ogni core di sapere di quali elementi si deve occupare
    int r; //resto della divisione intera

    float *a,*b,*c; //vettori , perchè puntatori ? per allocare dinamicamente la memoria

    printf("inseriere N\n");
    scanf("%d",&N);//inseriamo da tastiera la dimensione dei vettori

    /*allochiamo dinamicamente la memoria utilizziamo la funzione calloc per inizializzare a 0 i vettori 
        ne specifichiamo il numero di elementi e la dimensione in byte di ciascun elemento */
    a = (float *) calloc(N, sizeof(float));
    b = (float *) calloc(N, sizeof(float));
    c = (float *) calloc(N, sizeof(float));

    //la funzione calloc restituisce un puntatore a void, quindi lo castiamo a float

    //ora procediamo con l'inserimento da tastiera dei singoli elementi di ogni vettore
    printf("inserire i valori di a\n");
    for(i=0;i<N;i++){
        scanf("%f", &a[i]);
    }

    printf("inserire i valori di b\n");
    for(i=0;i<N;i++){
        scanf("%f", &b[i]);
    }

    #pragma omp parallel private(nloc,i,indice,id,step) shared(a,b,c,N,r) //dichiarazione della sezione parallela
    { //dichiariamo private le variabili che devono essere private per ogni thread

        t = omp_get_num_threads();//calcoliamo il numero di thread

        nloc = N/t ;//calcoliamo il numero di elementi da sommare per ogni thread facendo la divisione intera della 
                    //dimensione del vettore per il numero di thread

        r=N%t;//calcoliamo il resto della divisione intera

        id=omp_get_thread_num(); //la funzione restituisce id del thread e lo salva nella variabile

        printf("sono %d, di %d: numeri %d\n, r=%d\n",id,t,nloc,r);//stampa di controllo

        if (id < r){ //se l'id del thread è minore del resto della divisione intera
            nloc++; //incrementiamo il numero di elementi da sommare per ciascun thread
            step=0; //inizializziamo la variabile step a 0
        }

        else
            step=r;//altrimenti step è uguale al resto della divisione intera

        printf("sono %d, di %d: numeri %d\n, r=%d\n",id,t,nloc,r);//stampa di controllo

        for(i=0;i<nloc;i++){ //ciascun thread somma gli elementi dei vettori a e b
        //si parte da indice e si arriva a indice + nloc, perche ogni thread somma un numero di elementi pari a nloc
            indice = i + nloc * omp_get_thread_num() + step;//calcoliamo l'indice di partenza per ciascun thread
            c[indice] = a[indice] + b[indice]; //il risultato viene memorizzato nel vettore c
        }
    }

    //stampiamo il risultato
    printf("risultato della somma\n");
    for(i=0;i<N;i++){
        printf("%f\n",c[i]);
    }
}