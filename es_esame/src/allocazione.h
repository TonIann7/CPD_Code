#ifndef ALLOCAZIONE_H
#define ALLOCAZIONE_H

#define MAXVALUE 9

void allocationMatrix( int***, int, int );
void fillMatrix( int***, int, int );
void printMatrix( int**, int, int, char[] );
void deallocationMatrix( int***, int );

void allocationMatrixDouble(double***, int, int);
void fillMatrixDouble(double***, int, int);
void printMatrixDouble(double**, int, int, char[]);
void deallocationMatrixDouble(double***, int);

#endif // ALLOCAZIONE_H