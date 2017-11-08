#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#include "utils.h"


FILE *fopen_from_env(
        const char *env_var,
        const char *default_filename,
        const char *open_mode) {

    const char *filename = getenv(env_var);
    if(filename == NULL) {
        filename = default_filename;
    }

    FILE *fp = fopen(filename, open_mode);
    assert(fp != NULL);
    return fp;
}


// Prints each process's "my_columns" matrix
void debug_print(
        int rank, int num_procs,
        int n, int cols_per_process,
        float *my_columns) {

    for(int i = 0; i < rank; i++) {
        MPI_Barrier(MPI_COMM_WORLD);
    }

    printf("rank %d:\n", rank);
    for(int col = 0; col < cols_per_process; col++) {
        printf("  ");
        for(int row = 0; row < n; row++) {
            printf("%f ", my_columns[n*col + row]);
        }
        printf("\n");
    }
    fflush(stdout);  // Sempre dar descarga


    for(int i = 0; i < num_procs - rank; i++) {
        MPI_Barrier(MPI_COMM_WORLD);
    }

    fflush(stdout);
    MPI_Barrier(MPI_COMM_WORLD);
}


void scatter_cyclically(
        float *send_buffer,
        float *recv_buffer,
        int n, int num_procs)
{
    int cols_per_process = n / num_procs;

    MPI_Datatype aux_type, CyclicColumnsType;

    MPI_Type_vector(
            cols_per_process, n, n * num_procs,
            MPI_FLOAT, &aux_type);

    MPI_Type_create_resized(
            aux_type, 0, sizeof(float[n]),
            &CyclicColumnsType);

    MPI_Type_commit(&CyclicColumnsType);


    MPI_Scatter(
            send_buffer, 1, CyclicColumnsType,
            recv_buffer, n * cols_per_process, MPI_FLOAT,
            0, MPI_COMM_WORLD);

    MPI_Type_free(&CyclicColumnsType);

}


void gauss_jordan_elimination(
        int rank, int num_procs, int n, int pivot_index,
        float *pivot_column, float *my_columns) {
    int cols_per_process = n / num_procs;

    // Find 1st column to the right of pivot's column
    int initial_col = (pivot_index + num_procs - rank) / num_procs;

    #pragma omp parallel for
    for(int row = 0; row < n; row++) {
        for(int col = initial_col; col < cols_per_process; col++) {
            if(row != pivot_index) {
                float same_row = pivot_column[row];
                float same_col = my_columns[n*col + pivot_index];
                my_columns[n*col + row] -= same_row * same_col;
            }
        }
    }
}
