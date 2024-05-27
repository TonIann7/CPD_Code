#ifndef PARALLELCODE_H
#define PARALLELCODE_H 

int** createallocateMatrix(int rows, int columns);

int* createArray(int n);

int* createallocateArray(int n);

void printMatrix(int** matrix, int rows, int columns);

void printArray(int a[], int n);

void sum_vectors(float *a, float *b, float *c, int N);

float sum_numbers_first(float *a,int N);

float sum_numbers_second(float *a,int N);

double pigreco1(int N);

double pigreco2(int N);

double pigreco3(int N);

float prodottoscalare(float *a,float *b, int N);

int parallelsearch(int f,int l,int token,int n,int *a);

void oddEvenSort(int *a, int N);

void prodottoscalarematrice1(float **A, float B,int n,int m);

void prodottoscalarematrice2(float **A, float B,int n,int m);

void prodottoscalarematrice3(float **A, float alpha,int n,int m,int blockSize);

double * matxvet_righe(int m, int n, double *x, double **A);


#endif