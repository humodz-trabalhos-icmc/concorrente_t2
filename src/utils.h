#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>


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


void gauss_jordan_elimination(
        int rank, int num_procs, int n, int pivot_index,
        float *pivot_column, float *my_columns);

#endif
