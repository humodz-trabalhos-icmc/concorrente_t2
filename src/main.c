#include <stdio.h>
#include <mpi.h>
#include <omp.h>

int main(int argc, char **argv) {

    MPI_Init(&argc, &argv);

    puts("hello world");

    MPI_Finalize();
    return 0;
}
