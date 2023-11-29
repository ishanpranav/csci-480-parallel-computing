#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "../file.h"
#include "../file_stream.h"
#include "lab2.h"
#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

void printProgress(double percentage)
{
    int val = (int)(percentage * 100);
    int lpad = (int)(percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

/**
 * The main entry point for the application.
 *
 * @param count the number of command-line arguments.
 * @param args  a collection of command-line arguments. The length of the
 *              collection is given by the `count` parameter.
 * @return An exit code. This value is 0, indicating success, or 1, indicating
 *         a usage error.
 */
int main(int count, String args[])
{
    if (count != 3)
    {
        printf("Usage: lab2omp <n> <threads>\n");

        return 1;
    }

    long n = strtol(args[1], NULL, 10);

    // Since `n` can be up to 10,000,000 we need at least 32 bits (`long`) to
    // be standards-compliant.

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

    double start = omp_get_wtime();
    long *values = malloc((n - 1) * sizeof *values);
    long end = (n - 1) / 2;

#pragma omp parallel for num_threads(threads)
    for (long i = 0; i <= n - 2; i++)
    {
        values[i] = i + 2;
    }

    for (long i = 0; i <= end; i++)
    {
        printProgress((double)i / end);

        if (!values[i])
        {
            continue;
        }

#pragma omp parallel for num_threads(threads)
        for (long j = i + 1; j <= n - 2; j++)
        {
            if (values[j] && values[j] % values[i] == 0)
            {
                values[j] = 0;
            }
        }
    }

    lab2_write(n, values);
    free(values);
    printf("\ntime: %lf\n", omp_get_wtime() - start);

    return 0;
}
