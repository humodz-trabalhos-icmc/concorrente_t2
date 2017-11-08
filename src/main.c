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
#include "utils.h"

void print(
        int rank, int num_procs,
        int n, int cols_per_process,
        float *my_columns) {

    for(int i = 0; i < rank; i++) {
        MPI_Barrier(MPI_COMM_WORLD);
    }

    printf("rank %d:\n", rank);
    for(int col = 0; col < cols_per_process; col++) {
        printf("  ");
        for(int row = 0; row < 5; row++) {
            printf("%f ", my_columns[n*col + row]);
        }
        printf("\n");
    }
    fflush(stdout);


    for(int i = 0; i < num_procs - rank; i++) {
        MPI_Barrier(MPI_COMM_WORLD);
    }
}

void scatter_and_print(ColMajorMatrix *mat, int rank, int num_procs) {
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


    MPI_Datatype aux_type, CyclicColumnsType;

    MPI_Type_vector(
            cols_per_process, n, n * num_procs,
            MPI_FLOAT, &aux_type);

    MPI_Type_create_resized(
            aux_type, 0, sizeof(float[n]),
            &CyclicColumnsType);

    MPI_Type_commit(&CyclicColumnsType);


    MPI_Scatter(
            send_buf, 1, CyclicColumnsType,
            my_columns, n * cols_per_process, MPI_FLOAT,
            0, MPI_COMM_WORLD);

    MPI_Type_free(&CyclicColumnsType);


    float *bcast_buffer = malloc(sizeof(float[n]));
    assert(bcast_buffer != NULL);

    float *pivot_column = NULL;

    for(int pivot_index = 0; pivot_index < n; pivot_index++) {
        int pivot_owner = pivot_index % num_procs;
        int my_column_index = pivot_index / num_procs;

        int swap_indices[2] = {pivot_index, -1};

        if(rank == pivot_owner) {
            // Coluna com o pivo, que sera enviada por bcast
            pivot_column = &my_columns[n * my_column_index];

            // Pivoteia se o pivo for 0
            if(pivot_column[pivot_index] == 0) {
                for(int j = 0; j < n; j++) {
                    if(pivot_column[j] != 0) {
                        swap_indices[1] = j;
                        break;
                    }
                }

                assert(swap_indices[1] != -1); // Coluna inteira zerada, deu ruim
            }
        } else {
            // Buffer para receber coluna do pivo por bcast
            pivot_column = bcast_buffer;
        }

        // fala pra todo mundo quais linhas eh p trocar
        MPI_Bcast(swap_indices, 2, MPI_INT, pivot_owner, MPI_COMM_WORLD);

        // se der -1, nao precisa pivotear
        if(swap_indices[1] != -1) {
            swap_rows(
                    my_columns, n, cols_per_process,
                    swap_indices[0], swap_indices[1]);
        }


        // envia coluna do pivo
        MPI_Bcast(pivot_column, n, MPI_FLOAT, pivot_owner, MPI_COMM_WORLD);

        float pivot = pivot_column[pivot_index];

        // normalizacao (divide linha do pivo pelo pivo)
        for(int col = 0; col < cols_per_process; col++) {
            my_columns[n * col + pivot_index] /= pivot;
        }


        // acha 1a coluna que vem depois do pivo
        int initial_col = (pivot_index + num_procs - rank) / num_procs;
        initial_col = 0;

        // eliminacao (subtrai pelo produto)
        //#pragma omp parallel for
        for(int row = 0; row < n; row++) {
            for(int col = initial_col; col < cols_per_process; col++) {
                if(row != pivot_index) {
                    my_columns[n * col + row] -=
                        pivot_column[row] * my_columns[n * col + pivot_index];
                }
            }
        }

        // ta funcionando so 1 iter
        print(rank, num_procs, n, cols_per_process, my_columns);
    }

    free(bcast_buffer);
    free(my_columns);
}


int main(int argc, char **argv) {

    MPI_Init(&argc, &argv);

    int rank;
    int num_procs;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);


    const char *vector_txt = "input/20/vetor.txt";
    const char *matrix_txt = "input/20/matriz.txt";


    if(rank == 0) {
        FILE *vector_file = fopen(vector_txt, "r");
        FILE *matrix_file = fopen(matrix_txt, "r");

        assert(vector_file != NULL && matrix_file != NULL);

        Vector vec = Vector_read(vector_file);
        ColMajorMatrix mat = Matrix_read(matrix_file, vec.n);

        fclose(vector_file);
        fclose(matrix_file);


        scatter_and_print(&mat, rank, num_procs);

        Vector_free(&vec);
        Matrix_free(&mat);

    } else {
        scatter_and_print(NULL, rank, num_procs);
    }

    MPI_Finalize();
    return 0;
}
