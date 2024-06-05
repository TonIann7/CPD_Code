#ifndef PARALLELCODE_H
#define PARALLELCODE_H 

void sum_vectors(float *a, float *b, float *c, int N);

double *sommavettori2(int N,double *a,double *b,int th);

float sum_numbers_first(float *a,int N);

float sum_numbers_second(float *a,int N,int th);

int** createallocateMatrix(int rows, int columns);

int* createArray(int n);

int* createallocateArray(int n);

void printMatrix(int** matrix, int rows, int columns);

void printArray(int a[], int n);

double pigreco1(int N);

double pigreco2(int N);

double pigreco3(int N);

float prodottoscalare(float *a,float *b, int N);

int parallelsearch(int f,int l,int token,int n,int *a);

void oddEvenSort(int *a, int N);

void prodottoscalarematrice1(float **A, float B,int righe,int colonne,int th);

void prodottoscalarematrice2(float **A, float B,int righe,int colonne, int th);

void prodottoscalarematrice3(float **A, float alpha,int n,int m,int blockSize,int th);

double * matxvet_righe(int m, int n, double *x, double **A, int th);

double * matxvet_colonne(int righe, int colonne, double *x, double **A,int th);

double * matxvet_colonne2(int righe, int colonne, double *x, double **A,int th);

double * matxvet_colonne3(int righe, int colonne, double *x, double **A,int th);

double * matxvet_terzastrat(int righe,int colonne,int blocksize, double *x,double **A,int th);

#endif
