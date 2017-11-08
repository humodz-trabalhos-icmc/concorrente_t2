#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

#include "vector.h"


// Open file whose name is stored in an environment variable called
// @env_var. If the variable doesn't exist, use @default_filename
// instead. @open_mode is passed as the 2nd argument of fopen.
FILE *fopen_from_env(
        const char *env_var,
        const char *default_filename,
        const char *open_mode);


void debug_print(
        int rank, int num_procs,
        int n, int cols_per_process,
        float *my_columns);


void scatter_cyclically(
        float *send_buffer,
        float *recv_buffer,
        int n, int num_procs);


#define DONT_SWAP -1
#define SKIP_COLUMN -2

int pivot_swap(float *pivot_column, int pivot_index, int n);


void gauss_jordan_elimination(
        int rank, int num_procs, int n, int pivot_index,
        float *pivot_column, float *my_columns);


void update_result(
        int swap_index, int pivot_index,
        Vector *vec, float *pivot_column);

#endif
