#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>


typedef struct {
    float *data;
    int *indices;
    int n;
} Vector;

Vector Vector_read(FILE *fp);
void Vector_free(Vector *vec);
void Vector_print(Vector *vec, FILE *fp);
void Vector_swap(Vector *vec, int i, int j);


typedef struct {
    float *data;
    int n;
} ColMajorMatrix;

ColMajorMatrix Matrix_read(FILE *fp, int n);
void Matrix_free(ColMajorMatrix *mat);
void Matrix_print(ColMajorMatrix *mat, FILE *fp);



#endif
