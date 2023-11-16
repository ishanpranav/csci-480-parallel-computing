#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include "../core.h"
#include "lab1.h"

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
    if (count != 2)
    {
        printf("You need to enter the end number of the range\n");

        return 1;
    }

    int n = atoi(args[1]);

    MPI_Init(&count, &args);
    MPI_Barrier(MPI_COMM_WORLD);

    const int LAB1_RESULT_COUNT = 5;

    int rank;
    int size;
    int results[LAB1_RESULT_COUNT];
    int totals[LAB1_RESULT_COUNT];
    double start = MPI_Wtime();

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int length = ((n - 2) / size) + 1;
    int min = (length * rank) + 2;
    int max = min + length;

    if (rank == size - 1)
    {
        max = n;
    }
    else
    {
        max--;
    }
    
    if (max > n)
    {
        min = max + 1;
    }

    lab1_count_factors(min, max, 5, results, 2, 3, 5, 7, 13);
    MPI_Reduce(
        results,
        totals,
        LAB1_RESULT_COUNT,
        MPI_INT,
        MPI_SUM,
        0,
        MPI_COMM_WORLD);

    double end = MPI_Wtime();
    double elapsed;
    double localTime = end - start;

    MPI_Reduce(
        &localTime,
        &elapsed,
        1,
        MPI_DOUBLE,
        MPI_MAX,
        0,
        MPI_COMM_WORLD);
    MPI_Finalize();

    if (rank == 0)
    {
        printf("\nElapsed: %lf s\n", elapsed);
        lab1_print_factors(LAB1_RESULT_COUNT, totals, 2, 3, 5, 7, 13);
    }

    return 0;
}
