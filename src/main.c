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


void scatter_and_print_old(int rank, float *m, int n) {
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    float *col = malloc(sizeof(float[n]));
    assert(col != NULL);

    MPI_Scatter(
            m, n, MPI_FLOAT,
            col, n, MPI_FLOAT,
            0, MPI_COMM_WORLD);

    int num_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    for(int r = 0; r < num_procs; r++) {
        if(r == rank) {
            printf("rank %d: ", rank);
            for(int i = 0; i < n; i++) {
                printf("%f ", col[i]);
            }
            puts("");
            fflush(stdout);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }

    free(col);
}


void scatter_and_print(ColMajorMatrix *mat, int rank, int num_procs) {
    unsigned long long int n;
    float *send_buf = NULL;

    if(rank == 0) {
        n = mat->n;
        send_buf = mat->data;
    }

    MPI_Bcast(&n, 1, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);


    size_t cols_per_process = n / num_procs;
    float *recv_buf = malloc(sizeof(float[n * cols_per_process]));
    assert(recv_buf != NULL);

    // Send columns in rounds e.g. A B C A B C
    float *recv_buf_aux = recv_buf;
    for(size_t round = 0; round < cols_per_process; round++) {

        MPI_Scatter(
                send_buf, n, MPI_FLOAT,
                recv_buf_aux, n, MPI_FLOAT,
                0, MPI_COMM_WORLD);

        send_buf += n * num_procs;  // Skip to next block
        recv_buf_aux += n; // Skip to next column;
    }

    for(int round = 0; round < num_procs; round++) {
        if(round == rank) {
            printf("rank %d:\n", rank);

            for(size_t col = 0; col < cols_per_process; col++) {
                printf("  ");
                for(size_t row = 0; row < n; row++) {
                    printf("%f ", recv_buf[n*col + row]);
                }
                printf("\n");
            }
            fflush(stdout);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }

    free(recv_buf);
}


int main(int argc, char **argv) {

    MPI_Init(&argc, &argv);

    int rank;
    int num_procs;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);


    const char *vector_txt = "input/10/vetor.txt";
    const char *matrix_txt = "input/10/matriz.txt";


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
