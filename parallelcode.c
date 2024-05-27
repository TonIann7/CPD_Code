#include "parallelcode.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

// Implementazione della funzione per la somma di due vettori
void sum_vectors(float *a, float *b, float *c, int N) {
    int i; //indice per i cicli
    int t; //numero di thread
    int nloc; //numero di elementi per thread
    int indice; //indice di partenza per ciascun thread
    int id; //id del thread
    int step; //variabile di appogg
    int r; 
    #pragma omp parallel private(nloc,i,indice,id,step) shared(a,b,c,N,r) 
    
        
        t = omp_get_num_threads();//calcoliamo il numero di thread
        nloc = N/t ;//calcoliamo il numero di elementi da sommare per ogni thread
        //facendo la divisione intera della dimensione del vettore per il numero di thread
    r=N%t;//calcoliamo il resto della divisione intera
    id=omp_get_thread_num();
    printf("sono %d, di %d: numeri %d, r=%d\n", id, t, nloc); //stampa di controllo
    if (id < r) //se l'id del thread è minore del resto della divisione intera
    {
    nloc++; //incrementiamo il numero di elementi da sommare per ciascun thread
    step=0; //inizializziamo la variabile step a 0
    }
    else 
    step=r;//altrimenti step è uguale al resto della divisione intera
        printf("sono %d, di %d: numeri %d, r=%d, passo=%d\n",id,t,nloc,r,step);//stampa di controllo
        for(i=0;i<nloc;i++){ //ciascun thread somma gli elementi dei vettori a e b
        //si parte da indice e si arriva a indice+nloc, perche ogni thread somma un numero di elementi pari a nloc
            indice = i+nloc*omp_get_thread_num()+step;//calcoliamo l'indice di partenza per ciascun thread
            c[indice] = a[indice] + b[indice]; //il risultato viene memorizzato nel vettore c
        }
} 


 float sum_numbers_first(float *a,int N){
    int i; //dichiarazione variabili
    float sumtot=0; //dichiarazione variabile somma totale
    float sum; //dichiarazione variabile somma(parziale)
    int t; //dichiarazione variabile t(numero di thread)
    int nloc; //dichiarazione variabile nloc(numero di elementi per thread)
    int id; //dichiarazione variabile id(id del thread)
    int r; //dichiarazione variabile r(resto della divisione intera)
    int step; //dichiarazione variabile step
    int indice; //dichiarazione variabile indice

    #pragma omp parallel private(sum,nloc,id,step),shared(sumtot,t,r)
    {
        t = omp_get_num_threads();//calcoliamo il numero di thread
        nloc = N/t ; //calcoliamo il numero di elementi per thread
        r=N%t; //calcoliamo il resto della divisione intera
        id=omp_get_thread_num(); //calcoliamo l'id del thread
        if (id < r) //se l'id del thread è minore del resto della divisione intera
    {
    nloc++; //incrementiamo il numero di elementi da sommare per ciascun thread
    step=0; //inizializziamo la variabile step a 0
    }
    else {
    step=r;
    }
        sum=0; //inizializziamo la variabile sum a 0
        for (i=0;i<nloc;i++){ //ciclo for per sommare gli elementi dell'array
        //da i=0 a i=nloc ovvero il numero di elementi per thread
            indice = i+nloc*omp_get_thread_num()+step; //calcoliamo l'indice
            //che è uguale a i+numero di elementi per thread*id del thread+step
            //dove step è il resto della divisione intera
            sum=sum+a[indice];//somma degli elementi dell'array
        }
        sumtot=sumtot+sum;//somma totale
    }//fine blocco parallelo(direttiva)
    return sumtot;
 
}

float sum_numbers_second(float *a,int N){
    int i;
    float sumtot = 0;
   

    #pragma omp parallel for private(i) reduction(+:sumtot)
    for (i = 0; i < N; i++) {
        sumtot += a[i];
    }

    return sumtot;
}

double pigreco1(int N){
    long int i; //dichiarazione variabili
    double x, dx, f, sum, pi; //dichiarazione variabili
    sum = 0.0; //inizializzazione della variabile sum a 0
    dx = 1.0 / (double) N;
    #pragma omp parallel for private(x,f,i) shared(dx,sum,N)

    for (i = 1; i <= N; i++) //ciclo for da i=1 a i=n
    {
    x = dx * ((double) (i - 0.5)); //calcolo di x
    f = 4.0 / (1.0 + x*x); //calcolo di f
    sum = sum + f; //somma di f
    }
    pi = dx*sum; //calcolo di pi
    return pi;
    }

double pigreco2(int N){
    long int i; //dichiarazione variabili
    double x, dx, f, sum, pi; //dichiarazione variabili
    sum = 0.0; //inizializzazione della variabile sum a 0
    dx = 1.0 / (double) N;
    #pragma omp parallel for private(x,f,i) shared(dx,sum,N)

    for (i = 1; i <= N; i++) //ciclo for da i=1 a i=n
    {
    x = dx * ((double) (i - 0.5)); //calcolo di x
    f = 4.0 / (1.0 + x*x); //calcolo di f
    #pragma omp critical //direttiva critica
    sum = sum + f; //somma di f
    }
    pi = dx*sum; //calcolo di pi
    return pi;
    }

double pigreco3(int N){
    long int i; //dichiarazione variabili
    double x, dx, f, sum, pi; //dichiarazione variabili
    sum = 0.0; //inizializzazione della variabile sum a 0
    dx = 1.0 / (double) N;
    #pragma omp parallel for private(x,f,i) shared(dx,N) reduction(+:sum)

    for (i = 1; i <= N; i++) //ciclo for da i=1 a i=n
    {
    x = dx * ((double) (i - 0.5)); //calcolo di x
    f = 4.0 / (1.0 + x*x); //calcolo di f
    sum = sum + f; //somma di f
    }
    pi = dx*sum; //calcolo di pi
    return pi;
}

double * matxvet_righe(int m, int n, double *x, double **A){
    int i,j; //dichiarazione variabili
    double *b; //vettore risultante

    b=(double *)calloc(m,sizeof(double)); //allocazione dinamica del vettore risultante
    #pragma omp parallel for shared(m,n,x,A,b) private(i,j)
    for(i=0;i<n;i++){ //ciclo for da i=0 a i=n (righe della matrice)
        for(j=0;j<m;j++){ //ciclo for da j=0 a j=m (colonne della matrice)
            b[i]+=A[i][j]*x[j]; //calcolo del vettore risultante
            //la componente i-esima del vettore risultante è data dal prodotto scalare tra la riga i-esima della matrice e il j-esimo elemento del vettore x
        }
    }
    return b; //restituzione del vettore risultante
}

float prodottoscalare(float *a,float *b, int N){
    int i;
    float result;
    #pragma omp parallel for private(i) shared (a,b) reduction(+:result)
    for (i=0; i < N; i++) // calcolo il prodotto scalare
    result += (a[i] * b[i]); // sommo il prodotto scalare

    return result;
}

int parallelsearch(int f,int l,int token,int n,int *a){
    int index=-1; //indice di ritorno viene inizializzato a -1 per indicare che il valore non è stato trovato
    int size=(l-f)/n; //calcolo la dimensione di ogni blocco
    if(size==0 || n==1){ //se la dimensione del blocco è 0 oppure il numero di thread è 1
        #pragma omp parallel for //direttiva parallela
        for(int i=f;i<=l;i++){ //ciclo for per cercare il valore
            if(a[i]==token){ //se il valore è stato trovato
                index=i; //assegno l'indice alla variabile index
            }}
        return index; //ritorno l'indice
    }
        int left=f; //indice sinistro
        int right=l; //indice destro
        omp_set_num_threads(n); //imposto il numero di thread
        omp_set_nested(1);//abilito il nesting che sarebbe l'annidamento
        #pragma omp parallel //direttiva parallela
        {
            int id=omp_get_thread_num(); //ottengo l'id del thread
            int start=f+id*size; //calcolo l'indice iniziale dato da f+id*size perchè ogni thread deve partire da un indice diverso
            int end=start+size-1; //calcolo l'indice finale
            if(id==n-1){ //se l'id del thread è uguale al numero di thread -1
                end=l; //assegno l'indice finale a l
            }
            if(token>=a[start] && token<=a[end]){ //se il valore da cercare è compreso tra il valore iniziale e finale
                left=start; //assegno l'indice iniziale a left
                right=end; //assegno l'indice finale a right
            }
        }
        if(left==f && right==l){ //se left è uguale a f e right è uguale a l
            return -1; //ritorno -1 ovvero il valore non è stato trovato
        }
    
return parallelsearch(left,right,token,n,a); //ritorno la funzione ricorsiva
}



void oddEvenSort(int *a, int N){
    int sw=1; //variabile di appoggio
    int sw0; //variabile di appoggio
    int sw1=1;
    int start=0;//indice di partenza
    int i=0;
    int t=0;
    while(sw){//finchè sw è diverso da 0
    sw=0; //inizializzo sw a 0
    sw1=0; //inizializzo sw1 a 0
    #pragma omp parallel //direttiva parallela
    {
        int temp;//variabile di appoggio
        #pragma omp for //direttiva parallela
        for(i=0;i<N-1;i+=2){ //ciclo for per scorrere l'array ogni due elementi
            if(a[i]>a[i+1]){  //se l'elemento i è maggiore dell'elemento i+1
                temp=a[i]; //scambio gli elementi
                a[i]=a[i+1]; //scambio gli elementi
                a[i+1]=temp; //scambio gli elementi
                sw0=1; //imposto sw0 a 1
            }
        }
        if(sw0 || !t){ //se sw0 è diverso da 0 oppure t è diverso da 0
            #pragma omp for //Direttiva parallela
            
                for(i=1;i<N-1;i+=2){ //ciclo for per scorrere l'array ogni due elementi
                    if(a[i]>a[i+1]){ //se l'elemento i è maggiore dell'elemento i+1
                        temp=a[i];
                        a[i]=a[i+1];
                        a[i+1]=temp;
                        sw1=1;
                    }
                }
            
            t=1; //imposto t a 1
        }
    }

    }
}

void prodottoscalarematrice1(float **A, float B,int n,int m){

    int i,j;
    omp_set_num_threads(3);
    #pragma omp parallel for private(i,j) shared(A,B,n,m)//direttiva parallela 
    for(i=0;i<n;i++){//ciclo for per scorrere le righe della matrice
        for(j=0;j<m;j++){//ciclo for per scorrere le colonne della matrice
            A[i][j]*=B;//calcolo il prodotto tra la matrice e lo scalare
        
        }
    }
    for(i=0;i<n;i++){//ciclo for per scorrere le righe della matrice
        for(j=0;j<m;j++){
    printf("%f\n",A[i][j]);
        }
    }
}

void prodottoscalarematrice2(float **A, float B,int n,int m){
    int i,j;
    omp_set_num_threads(3);
    #pragma omp parallel for private(i,j) shared(A,B,n,m)//direttiva parallela 
    for(j=0;j<n;j++){//ciclo for per scorrere le righe della matrice
        for(i=0;i<m;i++){//ciclo for per scorrere le colonne della matrice
            A[i][j]*=B;//calcolo il prodotto tra la matrice e lo scalare
        
        }
    }
    for(i=0;i<n;i++){//ciclo for per scorrere le righe della matrice
        for(j=0;j<m;j++){
    printf("%f\n",A[i][j]);
        }
    }
}

void prodottoscalarematrice3(float **A, float alpha,int n,int m,int blockSize){
    int i,j;
    omp_set_num_threads(3);
    #pragma omp parallel for collapse(2)
    for (int blockRow = 0; blockRow < n; blockRow += blockSize) {
        for (int blockCol = 0; blockCol < m; blockCol += blockSize) {
            for (int i = blockRow; i < blockRow + blockSize && i < n; i++) {
                for (int j = blockCol; j < blockCol + blockSize && j < m; j++) {
                    A[i][j] *= alpha;
                }
            }
        }
    }

    for(i=0;i<n;i++){//ciclo for per scorrere le righe della matrice
        for(j=0;j<m;j++){
            printf("%f\n",A[i][j]);
        }
    }

}

int** createallocateMatrix(int rows, int columns) {
    int** matrix = (int**)malloc(rows * sizeof(int**));

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(columns * sizeof(int*));
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = rand() % 10 + 1;
        }
    }
    return matrix;
}

int* createArray(int n){
    int* array = (int*)calloc(n, sizeof (int));
    
    return array;
}

int* createallocateArray(int n){
    int* array = (int*)calloc(n, sizeof (int));
    srand(time(NULL));
    for (int i = 0; i < n; i++){
        array[i] = rand() % 5 + 1;
    }
    return array;
}

void printMatrix(int** matrix, int rows, int columns) {

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void printArray(int a[], int n){
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("\n");
}