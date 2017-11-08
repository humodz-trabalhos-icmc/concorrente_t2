#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <mpi.h>

// Data structure that stores the matrix in column-major order.
// E.g. the matrix
//   A D G
//   B E H
//   C F I
// Will be stored as [A B C D E F G H I]


typedef struct {
    float *data;
    int n;
} ColMajorMatrix;

ColMajorMatrix Matrix_read(FILE *fp, int n);
void Matrix_free(ColMajorMatrix *mat);
void Matrix_print(ColMajorMatrix *mat, FILE *fp);


// This function doesn't use the ColMajorMatrix struct.
// Swap rows i and i of a rows x cols matrix
void Matrix_swap_rows(
        float *col_major_matrix,
        int rows, int cols,
        int i, int j);


#endif
