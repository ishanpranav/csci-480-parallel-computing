#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include "../core.h"
#include "lab1.h"

/**
 * The main entry point for the application.
 *
 * @param count     the number of command-line arguments.
 * @param arguments a collection of command-line arguments. The length of the
 *                  collection is given by the `count` parameter.
 * @return An exit code. This value is always 0, indicating success.
 */
int main(int count, String arguments[])
{
    double localTime;
    double elapsed;

    if (count != 2)
    {
        printf("You need to enter the end number of the range\n");

        return 1;
    }

    int n = atoi(arguments[1]);

    MPI_Init(&count, &arguments);
    MPI_Barrier(MPI_COMM_WORLD);

    int rank;
    int size;
    double start = MPI_Wtime();

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int offset = 0;
    int length = n / size;
    int remainder = n % size;
    int results[5];

    lab1_count_factors(offset, length, 5, results, 2, 3, 5, 7, 13);

    double end = MPI_Wtime();

    localTime = end - start;

    MPI_Reduce(
        &localTime,
        &elapsed,
        1,
        MPI_DOUBLE,
        MPI_MAX,
        0,
        MPI_COMM_WORLD);
    MPI_Finalize();

    return 0;
}
