/**
 * Bruno Henrique Rasteiro 9292910
 * Hugo Moraes Dzin 8532186
 * Luiz Eduardo Dorici 4165850
 * Matheus Gomes da Silva Horta 8532321
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <mpi.h>

;
// Data structure that stores a square matrix in column-major order.
// E.g. the matrix
//   A D G
//   B E H
//   C F I
// Will be stored as the array [A B C D E F G H I], n = 3


typedef struct {
    float *data;
    int n;
} ColMajorMatrix;


ColMajorMatrix Matrix_read(FILE *fp, int n);
void Matrix_free(ColMajorMatrix *mat);
void Matrix_print(ColMajorMatrix *mat, FILE *fp);


// This function doesn't use the ColMajorMatrix struct.
// Swap rows @i and @j of a (@rows x @cols) matrix
void Matrix_swap_rows(
        float *col_major_matrix,
        int rows, int cols,
        int i, int j);


#endif
