/**
 * Bruno Henrique Rasteiro
 * Hugo Moraes Dzin 8532186
 * Luiz Eduardo Dorici
 * Matheus Gomes da Silva Horta
 */


#include <assert.h>
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

    MPI_Datatype aux, cols_type;
    MPI_Type_vector(cols_per_process, n, n * num_procs, MPI_FLOAT, &aux);
    MPI_Type_commit(&aux);
    MPI_Type_create_resized(aux, 0, sizeof(float[n]), &cols_type);
    MPI_Type_commit(&cols_type);

    MPI_Scatter(
            send_buf, 1, cols_type,
            my_columns, n * cols_per_process, MPI_FLOAT,
            0, MPI_COMM_WORLD);

    MPI_Type_free(&aux);
    MPI_Type_free(&cols_type);

    // Send columns in rounds e.g. A B C A B C
    float *my_columns_aux = my_columns;
    if(0)
    for(int round = 0; round < cols_per_process; round++) {

        MPI_Scatter(
                send_buf, n, MPI_FLOAT,
                my_columns_aux, n, MPI_FLOAT,
                0, MPI_COMM_WORLD);

        send_buf += n * num_procs;  // Skip to next block
        my_columns_aux += n; // Skip to next column;
    }

    print(rank, num_procs, n, cols_per_process, my_columns);

    /*
    float *bcast_column = malloc(sizeof(float[n]));
    assert(bcast_column != NULL);

    for(int i = 0; i < (int) n; i++) {
        int column_owner = (int) i % num_procs;
        int column_index = (int) i / num_procs;

        int swap_index[2] = {i, -1};

        // pivoteamento
        if(rank == column_owner) {
            float *pivot_col = &my_columns[n * column_index];

            if(pivot_col[i] == 0) {
                // Pula 0 .. i pois ja foram zeradas
                int j;
                for(j = i; j < (int) n; j++) {
                    if(pivot_col[j] != 0) {
                        swap_index[1] = j;
                        break;
                    }
                }

                assert(j != -1); // Tudo zero, deu ruim
            }
        }

        // fala pra todo mundo quais linhas eh p trocas
        MPI_Bcast(swap_index, 2, MPI_INT, column_owner, MPI_COMM_WORLD);

        // se der -1, nao precisa pioteat
        if(swap_index[1] != -1) {
            swap_rows(
                    my_columns, n, cols_per_process,
                    swap_index[0], swap_index[1]);
        }




        float *current_col = bcast_column;

        if(rank == column_owner) {
            current_col = &my_columns[column_index * n];
        }

        // envia coluna do pivo
        MPI_Bcast(current_col, n, MPI_FLOAT, column_owner, MPI_COMM_WORLD);

        float pivot = current_col[i];

        // normalizacao (divide linha do pivo pelo pivo)
        for(int col = 0; col < cols_per_process; col++) {
            my_columns[n * col + i] /= pivot;
        }


        // acha 1a coluna que vem depois do pivo
        int initial_col = (i + num_procs - rank) / num_procs;
        (void) initial_col;

        // eliminacao (subtrai pelo produto)
        //#pragma omp parallel for
        for(int row = 0; row < (int) n; row++) {
            for(int col = 0; col < cols_per_process; col++) {
                if(row != i) {
                    my_columns[n * col + row] -=
                        current_col[row] * my_columns[n * col + i];
                }
            }
        }

        // ta funcionando so 1 iter
        for(int round = 0; round < num_procs; round++) {
            if(round == rank) {
                printf("rank %d:\n", rank);

                for(int col = 0; col < cols_per_process; col++) {
                    printf("  ");
                    for(int row = 0; row < (int)n; row++) {
                        printf("%f ", my_columns[n*col + row]);
                    }
                    printf("\n");
                }
                fflush(stdout);
            }
            MPI_Barrier(MPI_COMM_WORLD);
        }
    }


    free(bcast_column);/**/
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
