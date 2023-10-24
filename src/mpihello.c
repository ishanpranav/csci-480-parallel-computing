#include <mpi.h>
#include <stdio.h>
#include "core.h"

/**
 * The main entry point for the application.
 *
 * @param count     The number of command-line arguments.
 * @param arguments An collection of command-line arguments. The length of the
 *                  collection is given by the `count` parameter.
 * @return An exit code. This value is always 0, indicating success.
 */
int main(int count, StringArray arguments)
{
    int rank;
    int size;

    MPI_Init(&count, &arguments);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("Hello from process %i of %i\n", rank, size);
    MPI_Finalize();

    return 0;
}
