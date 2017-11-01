#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>


float *mat_new(int n) {
    float *m = malloc(n * (n+1) * sizeof(float));
    assert(m != NULL);
    return m;
}


void mat_free(float *m) {
    free(m);
}


float *mat_read(FILE *fp, int *np) {
    fscanf(fp, " %d", np);
    int n = *np;

    assert(n > 0);

    float *m = mat_new(n);

    for(int row = 0; row < n; row++) {
        for(int col = 0; col < n + 1; col++) {
            fscanf(fp, " %f", &m[n*col + row]);
        }
    }

    return m;
}


void mat_print(FILE *fp, float *m, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n + 1; j++) {
            fprintf(fp, "%f ", m[n*j + i]);
        }
        fprintf(fp, "\n");
    }
}



void scatter_and_print(int rank, float *m, int n) {
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    float *col = malloc(sizeof(float[n]));
    assert(col != NULL);

    int err = MPI_Scatter(
            m, n, MPI_FLOAT,
            col, n, MPI_FLOAT,
            0, MPI_COMM_WORLD);

    if(err != MPI_SUCCESS) {
        printf("aff\n");
    }

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

    int n;
    if(rank == 0) {
        float *m = mat_read(stdin, &n);

        mat_print(stdout, m, n);
        scatter_and_print(rank, m, n);

        mat_free(m);
    } else {
        scatter_and_print(rank, NULL, 0);
    }

    MPI_Finalize();
    return 0;
}
