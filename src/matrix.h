#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>


typedef struct {
    float *data;
    size_t n;
} ColMajorMatrix;


typedef struct {
    float *data;
    size_t n;
} Vector;


Vector Vector_read(FILE *fp);
ColMajorMatrix Matrix_read(FILE *fp, size_t n);
void Matrix_free(ColMajorMatrix *mat);
void Vector_free(Vector *vec);
void Matrix_print(ColMajorMatrix *mat, FILE *fp);
void Vector_print(Vector *vec, FILE *fp);


#endif
