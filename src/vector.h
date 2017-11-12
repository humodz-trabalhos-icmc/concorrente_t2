/**
 * Bruno Henrique Rasteiro 9292910
 * Hugo Moraes Dzin 8532186
 * Luiz Eduardo Dorici 4165850
 * Matheus Gomes da Silva Horta 8532321
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>

// Data structure that stores the result vector.
// By using only Vector_swap to swap rows, this struct remembers
// the correct order of its elements, that will be used by
// Vector_print to write the result to a text file.


typedef struct {
    float *data;
    int *indices;  // stores correct order of elements
    int n;
} Vector;


Vector Vector_read(FILE *fp);
void Vector_free(Vector *vec);
void Vector_print(Vector *vec, FILE *fp);
void Vector_swap_rows(Vector *vec, int i, int j);

#endif  // VECTOR_H
