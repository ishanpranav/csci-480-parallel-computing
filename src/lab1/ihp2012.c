// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav. All rights reserved.
// Licensed under the MIT License.

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

/** Represents text as a zero-terminated sequence of characters. */
typedef char* String;

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

    int n = atoi(arguments[1]);

    MPI_Init(&count, &arguments);
    MPI_Barrier(MPI_COMM_WORLD);

    const int LAB1_RESULT_COUNT = 5;

    int rank;
    int size;
    int factors[] = {2, 3, 5, 7, 13};
    int results[] = {0, 0, 0, 0, 0};
    int totals[LAB1_RESULT_COUNT];
    double start = MPI_Wtime();

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int length = ((n - 2) / size) + 1;
    int min = (length * rank) + 2;
    int max = min + length;

    if (rank == size - 1)
    {
        // The last process handles the remainder.

        max = n;
    }
    else
    {
        // Adding 1 to the length ensured the length was not 0 in the case when
        // the number of processes is greater than the number of elements. Now
        // the extra 1 can be removed.

        max--;
    }
    
    if (max > n)
    {
        // If the number of processes is greater than the number of elements,
        // then we will overshoot, since we set the length to 1. So some of the
        // processes are redundant and will be idle. We can create the
        // illogical range [max + 1, max] to make sure the process does nothing.

        min = max + 1;
    }

    for (int i = min; i <= max; i++)
    {
        for (int j = 0; j < LAB1_RESULT_COUNT; j++)
        {
            if (i % factors[j] == 0)
            {
                results[j]++;
            }
        }
    }

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

    // Only process 0 will print to the standard output stream.

    if (rank != 0)
    {
        return 0;
    }

    printf("%lf s elapsed\n", elapsed);

    for (int j = 0; j < LAB1_RESULT_COUNT; j++)
    {
        printf("%d: %d\n", factors[j], totals[j]);
    }

    return 0;
}
