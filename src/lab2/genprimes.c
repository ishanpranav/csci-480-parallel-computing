// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav. All rights reserved.
// Licensed under the MIT License.

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/** Represents text as a zero-terminated sequence of characters. */
typedef char *String;

/**
 * The main entry point for the application.
 *
 * @param count the number of command-line arguments.
 * @param args  a collection of command-line arguments. The length of the
 *              collection is given by the `count` parameter. By convention,
 *              the first argument is the name of the program.
 * @return An exit code. This value is 0, indicating success, or 1, indicating
 *         a usage or system error.
 */
int main(int count, String args[])
{
    if (count != 3)
    {
        printf("Usage: genprimes <n> <threads>\n");

        return 1;
    }

    // Since `n` can be up to 10,000,000 we need at least 32 bits (`long`).

    long n = atol(args[1]);

    if (n < 2 || n > 10000000)
    {
        printf("<n> must be a positive number between 2 and 10,000,000.\n");

        return 1;
    }

    int threads = atoi(args[2]);

    if (threads < 0)
    {
        printf("<threads> must be a positive number.\n");

        return 1;
    }

    // Track whether each of the numbers in [2, n] is composite (crossed out)
    // We track composites rather than primes so that we can use calloc()

    bool *composites = calloc((n - 1), sizeof *composites);

    if (!composites)
    {
        fprintf(stderr, "Error: Out of memory.\n");

        return 1;
    }

    /**
     * FOR i := 2 TO (n + 1) / 2
     *      IF i is crossed out THEN NEXT
     *
     *      PARALLEL FOR j := i + 1 TO n
     *          IF j is crossed out THEN NEXT
     *          IF i divides j THEN cross out j
     *      NEXT
     * NEXT
     */

    /*
     * PARALLEL FOR i := 2 TO (n + 1) / 2
     *      IF i is crossed out THEN NEXT
     *
     *      FOR j := 2i TO n STEP i
     *          cross out j
     *      NEXT
     * NEXT
     */

    double start = omp_get_wtime();
    long end = (n + 1) / 2;

    // Implementation of the second (faster) algorithm

#pragma omp parallel for num_threads(threads)
    for (long i = 2; i <= end; i++)
    {
        if (composites[i - 2])
        {
            continue;
        }

        for (long j = i * 2; j <= n; j += i)
        {
            composites[j - 2] = true;
        }
    }

    double elapsed = omp_get_wtime() - start;

    printf("time: %lf\n", elapsed);

    // We only need 13 characters in the buffer since the longest valid file
    // name is "10000000.txt" (12 characters terminated by '\0').

    char buffer[13];

    sprintf(buffer, "%ld.txt", n);

    FILE *stream = fopen(buffer, "w");

    if (!stream)
    {
        fprintf(stderr, "Error: I/O.\n");

        return 1;
    }

    for (long i = 0; i <= n - 2; i++)
    {
        if (composites[i])
        {
            continue;
        }

        fprintf(stream, "%ld ", i + 2);
    }

    fclose(stream);
    free(composites);

    return 0;
}
