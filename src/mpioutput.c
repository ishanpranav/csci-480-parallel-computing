#include <mpi.h>
#include <stdio.h>

/** Represents text as a zero-terminated sequence of characters. */
typedef char *String;

/**
 * The main entry point for the application.
 *
 * @param count the number of command-line arguments.
 * @param args  a collection of command-line arguments. The length of the
 *              collection is given by the `count` parameter.
 * @return An exit code. This value is always 0, indicating success.
 */
int main(int count, String args[])
{
    int rank;
    int size;

    MPI_Init(&count, &args);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("Proc %d of %d > Does anyone have a toothpick?\n", rank, size);
    MPI_Finalize();

    return 0;
}
