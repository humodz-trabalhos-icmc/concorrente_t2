#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"


ColMajorMatrix Matrix_read(FILE *fp, int n) {
    ColMajorMatrix mat;

    mat.n = n;
    mat.data = malloc(sizeof(float[n][n]));
    assert(mat.data != NULL);

    for(int row = 0; row < n; row++) {
        for(int col = 0; col < n; col++) {
            assert(!feof(fp));
            fscanf(fp, " %f", &mat.data[n*col + row]);
        }
    }

    return mat;
}


void Matrix_free(ColMajorMatrix *mat) {
    free(mat->data);
    mat->data = NULL;
}


void Matrix_print(ColMajorMatrix *mat, FILE *fp) {
    for(int i = 0; i < mat->n; i++) {
        for(int j = 0; j < mat->n; j++) {
            fprintf(fp, "%f ", mat->data[mat->n*j + i]);
        }
        fprintf(fp, "\n");
    }
}


void Matrix_swap_rows(
        float *mat,
        int rows, int cols,
        int i, int j) {
    float aux;
    for(int col = 0; col < cols; col++) {
        aux = mat[col * rows + i];
        mat[col * rows + i] = mat[col * rows + j];
        mat[col * rows + j] = aux;
    }
}
