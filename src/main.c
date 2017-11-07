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


void scatter_and_print(int rank, float *m, int n) {
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

        Vector_print(&vec, stdout);
        Matrix_print(&mat, stdout);

        fclose(vector_file);
        fclose(matrix_file);

        Vector_free(&vec);
        Matrix_free(&mat);


        //scatter_and_print(rank, m, n);

    } else {
        //scatter_and_print(rank, NULL, 0);
    }

    MPI_Finalize();
    return 0;
}
