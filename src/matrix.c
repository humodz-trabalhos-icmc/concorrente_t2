#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"


Vector Vector_read(FILE *fp) {
    Vector vec;
    size_t capacity = 1000;

    vec.n = 0;
    vec.data = malloc(sizeof(float[capacity]));
    assert(vec.data != NULL);

    float num;

    fscanf(fp, " %f", &num);
    while( ! feof(fp)) {
        if(vec.n == capacity) {
            capacity *= 2;
            vec.data = realloc(vec.data, sizeof(float[capacity]));
            assert(vec.data != NULL);
        }

        vec.data[vec.n] = num;
        vec.n += 1;

        fscanf(fp, " %f", &num);
    }

    if(vec.n < capacity) {
        vec.data = realloc(vec.data, sizeof(float[vec.n]));
    }

    return vec;
}


ColMajorMatrix Matrix_read(FILE *fp, size_t n) {
    ColMajorMatrix mat;

    mat.n = n;
    mat.data = malloc(sizeof(float[n][n]));
    assert(mat.data != NULL);

    for(size_t row = 0; row < n; row++) {
        for(size_t col = 0; col < n; col++) {
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


void Vector_free(Vector *vec) {
    free(vec->data);
    vec->data = NULL;
}


void Matrix_print(ColMajorMatrix *mat, FILE *fp) {
    for(size_t i = 0; i < mat->n; i++) {
        for(size_t j = 0; j < mat->n; j++) {
            fprintf(fp, "%f ", mat->data[mat->n*j + i]);
        }
        fprintf(fp, "\n");
    }
}


void Vector_print(Vector *vec, FILE *fp) {
    for(size_t i = 0; i < vec->n; i++) {
            fprintf(fp, "%f ", vec->data[i]);
    }
    fprintf(fp, "\n");
}
