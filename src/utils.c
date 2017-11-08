#include "utils.h"


void swap_rows(float *mat, int rows, int cols, int i, int j) {
    float aux;
    for(int col = 0; col < cols; col++) {
        aux = mat[col * rows + i];
        mat[col * rows + i] = mat[col * rows + j];
        mat[col * rows + j] = aux;
    }
}
