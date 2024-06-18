#include "allocazione.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Procedura utilizzata per l'allocazione della matrice
 * 
 * @param matrix matrice da allocare
 * @param N righe della matrice
 * @param M colonne della matrcie
*/
void allocationMatrix( int*** matrix, int N, int M ) {
    *matrix = ( int** ) calloc( N, sizeof( int* ) );
    for ( int i = 0; i < N; i++ )
        ( *matrix )[i] = ( int* ) calloc( M, sizeof( int ) );
}

void allocationMatrixDouble(double*** matrix, int N, int M) {
    *matrix = (double**) calloc(N, sizeof(double*));
    for (int i = 0; i < N; i++)
        (*matrix)[i] = (double*) calloc(M, sizeof(double));
}


/**
 * Procedura utilizzata per il riempimento della matrice
 * 
 * @param matrix matrice da allocare
 * @param N righe della matrice
 * @param M colonne della matrcie
*/
void fillMatrix( int*** matrix, int N, int M ) {
    for ( int i = 0; i < N; i++ )
        for ( int j = 0; j < M; j++ )
            ( *matrix )[i][j] = rand() % MAXVALUE + 1;
}

void fillMatrixDouble(double*** matrix, int N, int M) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            (*matrix)[i][j] = rand() % MAXVALUE + 1;
}

/**
 * Procedura utilizzata per la stampa della matrice
 * 
 * @param matrix matrice da allocare
 * @param N righe della matrice
 * @param M colonne della matrcie
 * @param name nome della matrice
*/
void printMatrix( int** matrix, int N, int M, char name[] ) {
    printf( "\n%s:\n", name );
    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < M; j++ )
            printf( "%d    ", matrix[i][j] );
        printf( "\n" );
    }
}

void printMatrixDouble(double** matrix, int N, int M, char name[]) {
    printf("\n%s:\n", name);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            printf("%lf    ", matrix[i][j]);
        printf("\n");
    }
}

/**
 * Procedura utilizzata per la deallocazione della matrice
 * 
 * @param matrix matrice da allocare
 * @param N righe della matrice
*/
void deallocationMatrix( int*** matrix, int N ) {
    for ( int i = 0; i < N; i++ )
        free( ( *matrix )[i] );
    free( *matrix );
}

void deallocationMatrixDouble(double*** matrix, int N) {
    for (int i = 0; i < N; i++)
        free((*matrix)[i]);
    free(*matrix);
}