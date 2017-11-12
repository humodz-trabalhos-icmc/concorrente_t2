/**
 * Bruno Henrique Rasteiro 9292910
 * Hugo Moraes Dzin 8532186
 * Luiz Eduardo Dorici 4165850
 * Matheus Gomes da Silva Horta 8532321
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

#include "matrix.h"
#include "vector.h"
#include "utils.h"


void gauss_jordan(
        ColMajorMatrix *mat, Vector *vec,
        int rank, int num_procs);


int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank;
    int num_procs;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);


    // Only master process does input/output
    if(rank == 0) {
        // Load inputs, do calculation, save result
        FILE *vector_file = fopen_from_env(
                "OMPI_VECTOR_FILE", "vetor.txt", "r");

        Vector vec = Vector_read(vector_file);
        fclose(vector_file);


        FILE *matrix_file = fopen_from_env(
                "OMPI_MATRIX_FILE", "matriz.txt", "r");

        ColMajorMatrix mat = Matrix_read(matrix_file, vec.n);
        fclose(matrix_file);


        gauss_jordan(&mat, &vec, rank, num_procs);


        FILE *result_file = fopen_from_env(
                "OMPI_RESULT_FILE", "resultado.txt", "w");

        Vector_print(&vec, result_file);
        fclose(result_file);

        Vector_free(&vec);
        Matrix_free(&mat);

    } else {
        gauss_jordan(NULL, NULL, rank, num_procs);
    }

    MPI_Finalize();
    return 0;
}


void gauss_jordan(
        ColMajorMatrix *mat, Vector *vec,
        int rank, int num_procs) {
    // At this point, only master knows mat, vec and n

    int n;
    float *send_buffer = NULL;

    if(rank == 0) {
        n = (int) mat->n;
        send_buffer = mat->data;
    }

    // Tell everyone the order of the matrix (n)
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);


    // Divide matrix between processes
    assert(n % num_procs == 0);
    int cols_per_process = n / num_procs;

    float *my_columns = malloc(sizeof(float[n * cols_per_process]));
    assert(my_columns != NULL);

    scatter_cyclically(send_buffer, my_columns, n, num_procs);


    // These are used when broadcasting the pivot's whole column
    float *pivot_column = NULL;
    float *bcast_buffer = malloc(sizeof(float[n]));
    assert(bcast_buffer != NULL);


    for(int pivot_index = 0; pivot_index < n; pivot_index++) {
        // Which row to swap pivot with
        int swap_index;
        // Rank of process that has the pivot
        int pivot_owner = pivot_index % num_procs;

        if(rank == pivot_owner) {
            int my_pivot_col_index = pivot_index / num_procs;

            // If I own pivot -> store its column in pivot_column
            pivot_column = &my_columns[n * my_pivot_col_index];

            // Check if it's necessary to swap pivot with someone else
            // This happend when pivot == 0
            swap_index = pivot_swap(pivot_column, pivot_index, n);
        } else {
            // If I don't own pivot -> point pivot_column to a receive buffer
            pivot_column = bcast_buffer;
        }

        // Tell everyone which rows to swap
        MPI_Bcast(&swap_index, 1, MPI_INT, pivot_owner, MPI_COMM_WORLD);


        if(swap_index > 0) {
            Matrix_swap_rows(
                    my_columns, n, cols_per_process,
                    pivot_index, swap_index);
        } else if(swap_index == SKIP_COLUMN) {
            // Whole column is zeros -> skip computations
            continue;
        }

        // Broadcast pivot's column
        MPI_Bcast(pivot_column, n, MPI_FLOAT, pivot_owner, MPI_COMM_WORLD);


        float pivot = pivot_column[pivot_index];
        assert(pivot != 0);

        // Update result vector
        if(rank == 0) {
            update_result(
                    swap_index, pivot_index,
                    vec, pivot_column);
        }

        // Normalization (divide pivot's row by the pivot
        for(int col = 0; col < cols_per_process; col++) {
            my_columns[n*col + pivot_index] /= pivot;
        }

        gauss_jordan_elimination(
                rank, num_procs, n, pivot_index,
                pivot_column, my_columns);
    }

    // main() is responsible for saving the result to a file

    free(bcast_buffer);
    free(my_columns);
}

