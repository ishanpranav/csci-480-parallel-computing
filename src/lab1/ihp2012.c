// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav. All rights reserved.
// Licensed under the MIT License.

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#define RESULT_COUNT 5

/** Represents text as a zero-terminated sequence of characters. */
typedef char *String;

/**
 * Counts the multiples in a relevant range.
 *
 * @param min     the inclusive lower bound of the iteration.
 * @param max     the inclusive upper bound of the iteration.
 * @param count   the number of factors.
 * @param results the `count`-sized output buffer, followed by `count` factors
 *                supplied as a parameterized array.
 */
static void multiples(long min, long max, long count, long results[], ...)
{
    for (long j = 0; j < count; j++)
    {
        results[j] = 0;
    }

    va_list params;

    for (long i = min; i <= max; i++)
    {
        va_start(params, results);

        for (long j = 0; j < count; j++)
        {
            if (i % va_arg(params, long) == 0)
            {
                results[j]++;
            }
        }

        va_end(params);
    }
}

/**
 * Prints the number of multiples in the range.
 *
 * @param count   the number of factors.
 * @param results the `count`-sized output buffer, followed by `count` factors
 *                supplied as a parameterized array.
 */
static void write(long count, long results[], ...)
{
    va_list params;

    va_start(params, results);

    for (long j = 0; j < count; j++)
    {
        printf("%ld: %ld\n", va_arg(params, long), results[j]);
    }

    va_end(params);
}

/**
 * The main entry point for the application.
 *
 * @param count the number of command-line arguments.
 * @param args  a collection of command-line arguments. The length of the
 *              collection is given by the `count` parameter. By convention,
 *              the first argument is the name of the program.
 * @return This value is 0, indicating success, or 1, indicating
 *         a usage error.
 */
int main(int count, String args[])
{
    if (count != 2)
    {
        printf("You need to enter the end number of the range\n");

        return 1;
    }

    long n = atoi(args[1]);

    MPI_Init(&count, &args);
    MPI_Barrier(MPI_COMM_WORLD);

    int rank;
    int size;
    long results[RESULT_COUNT];
    long totals[RESULT_COUNT];
    double start = MPI_Wtime();

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long length = ((n - 2) / size) + 1;
    long min = (length * rank) + 2;
    long max = min + length;

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

    multiples(min, max, 5, results, 2, 3, 5, 7, 13);
    MPI_Reduce(
        results,
        totals,
        RESULT_COUNT,
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
        printf("Elapsed: %lf s\n", elapsed);
        write(RESULT_COUNT, totals, 2, 3, 5, 7, 13);
    }

    return 0;
}
