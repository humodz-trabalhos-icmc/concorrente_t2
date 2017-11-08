#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"


Vector Vector_read(FILE *fp) {
    Vector vec;
    int capacity = 1000;

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

    vec.indices = malloc(sizeof(int[vec.n]));
    assert(vec.indices != NULL);

    for(int i = 0; i < vec.n; i++) {
        vec.indices[i] = i;
    }

    return vec;
}


void Vector_free(Vector *vec) {
    free(vec->data);
    free(vec->indices);
    vec->data = NULL;
    vec->indices = NULL;
}


void Vector_print(Vector *vec, FILE *fp) {
    for(int i = 0; i < vec->n; i++) {
        int pos = vec->indices[i];
        fprintf(fp, "%f\n", vec->data[pos]);
    }
}


void Vector_swap(Vector *vec, int i, int j) {
    float f = vec->data[i];
    vec->data[i] = vec->data[j];
    vec->data[j] = f;

    int s = vec->indices[i];
    vec->indices[i] = vec->indices[j];
    vec->indices[j] = s;
}


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

