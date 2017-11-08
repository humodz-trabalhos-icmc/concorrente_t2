/**
 * Bruno Henrique Rasteiro
 * Hugo Moraes Dzin 8532186
 * Luiz Eduardo Dorici
 * Matheus Gomes da Silva Horta
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
        FILE *vector_file = fopen_from_env(
                "GJ_VECTOR_FILE", "vetor.txt", "r");

        Vector vec = Vector_read(vector_file);
        fclose(vector_file);

        FILE *matrix_file = fopen_from_env(
                "GJ_MATRIX_FILE", "matriz.txt", "r");

        ColMajorMatrix mat = Matrix_read(matrix_file, vec.n);
        fclose(matrix_file);


        gauss_jordan(&mat, &vec, rank, num_procs);


        FILE *result_file = fopen_from_env(
                "GJ_RESULT_FILE", "resultado.txt", "w");

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
    int n;
    float *send_buf = NULL;

    if(rank == 0) {
        n = (int) mat->n;
        send_buf = mat->data;
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);


    int cols_per_process = n / num_procs;

    float *my_columns = malloc(sizeof(float[n * cols_per_process]));
    assert(my_columns != NULL);

    scatter_cyclically(send_buf, my_columns, n, num_procs);

    float *bcast_buffer = malloc(sizeof(float[n]));
    assert(bcast_buffer != NULL);

    float *pivot_column = NULL;

    for(int pivot_index = 0; pivot_index < n; pivot_index++) {
        int pivot_owner = pivot_index % num_procs;
        int swap_index = -1;

        if(rank == pivot_owner) {
            int my_pivot_column = pivot_index / num_procs;

            // Coluna com o pivo, que sera enviada por bcast
            pivot_column = &my_columns[n * my_pivot_column];

            // Pivoteia se o pivo for 0
            if(pivot_column[pivot_index] == 0) {
                swap_index = -2;

                for(int j = pivot_index; j < n; j++) {
                    if(pivot_column[j] != 0) {
                        swap_index = j;
                        break;
                    }
                }
            }
        } else {
            // Buffer para receber coluna do pivo por bcast
            pivot_column = bcast_buffer;
        }

        // fala pra todo mundo quais linhas eh p trocar
        MPI_Bcast(&swap_index, 1, MPI_INT, pivot_owner, MPI_COMM_WORLD);

        // se der -1, nao precisa pivotear
        if(swap_index > 0) {
            Matrix_swap_rows(
                    my_columns, n, cols_per_process,
                    pivot_index, swap_index);
        } else if(swap_index == -2) {
            continue;
        }


        // envia coluna do pivo
        MPI_Bcast(pivot_column, n, MPI_FLOAT, pivot_owner, MPI_COMM_WORLD);


        float pivot = pivot_column[pivot_index];
        assert(pivot != 0);

        // Operaçoes no vetor resposta
        if(rank == 0) {
            if(swap_index > 0) {
                Vector_swap_rows(vec, pivot_index, swap_index);
            }

            vec->data[pivot_index] /= pivot;

            for(int row = n -1; row >= 0; row--) {
                if(row != pivot_index) {
                    vec->data[row] -=
                        pivot_column[row] * vec->data[pivot_index];
                }
            }
        }


        // normalizacao (divide linha do pivo pelo pivo)
        for(int col = 0; col < cols_per_process; col++) {
            my_columns[n*col + pivot_index] /= pivot;
        }

        // acha 1a coluna que vem depois do pivo
        int initial_col = (pivot_index + num_procs - rank) / num_procs;
        //initial_col = 0;

        // eliminacao (subtrai pelo produto)
        #pragma omp parallel for
        for(int row = 0; row < n; row++) {
            for(int col = initial_col; col < cols_per_process; col++) {
                if(row != pivot_index) {
                    if(0)if(rank == 0 && col == 1) {
                        printf("%f, %f\n",
                        pivot_column[row], my_columns[n*col + pivot_index]);
                    }
                    my_columns[n*col + row] -=
                        pivot_column[row] * my_columns[n*col + pivot_index];
                }
            }
        }
    }


    //print(rank, num_procs, n, cols_per_process, my_columns);
    if(rank == 0){
        for(int row = 0; row < n; row++)
            printf("%f\n", vec->data[row]);
    }


    free(bcast_buffer);
    free(my_columns);
}

