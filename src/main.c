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
            fscanf(fp, " %f", &m[(n+1) * row + col]);
        }
    }

    return m;
}


void mat_print(FILE *fp, float *m, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n + 1; j++) {
            fprintf(fp, "%f ", m[(n+1) * i + j]);
        }
        fprintf(fp, "\n");
    }
}


int main(int argc, char **argv) {

    MPI_Init(&argc, &argv);

    int n;
    float *m = mat_read(stdin, &n);

    mat_print(stdout, m, n);

    mat_free(m);

    MPI_Finalize();
    return 0;
}
