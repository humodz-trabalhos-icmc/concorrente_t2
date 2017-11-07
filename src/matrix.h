#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>


typedef struct {
    float *data;
    size_t *indices;
    size_t n;
} Vector;

Vector Vector_read(FILE *fp);
void Vector_free(Vector *vec);
void Vector_print(Vector *vec, FILE *fp);
void Vector_swap(Vector *vec, size_t i, size_t j);


typedef struct {
    float *data;
    size_t n;
} ColMajorMatrix;

ColMajorMatrix Matrix_read(FILE *fp, size_t n);
void Matrix_free(ColMajorMatrix *mat);
void Matrix_print(ColMajorMatrix *mat, FILE *fp);



#endif
