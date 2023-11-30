#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * The main entry point for the application.
 *
 * @param count the number of command-line arguments.
 * @param args  a collection of command-line arguments. The length of the
 *              collection is given by the `count` parameter.
 * @return An exit code. This value is 0, indicating success, or 1, indicating
 *         a usage error.
 */
int main(int count, char *args[])
{
    if (count != 3)
    {
        printf("Usage: genprimes <n> <threads>\n");

        return 1;
    }

    // Since `n` can be up to 10,000,000 we need at least 32 bits (`long`).

    long n = strtol(args[1], NULL, 10);

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

    bool *composites = calloc((n - 1), sizeof *composites);
    long end = n - 2;

    if (!composites)
    {
        printf("Error: Out of memory.\rn");

        return 1;
    }

    /**
     * FOR EACH factor IN [2, (n + 1) / 2]
     *  IF factor is crossed out THEN NEXT
     *  FOR EACH product IN [factor + 1, n]
     *   IF product is crossed out THEN NEXT
     *   IF product is divisible by factor THEN cross out product
     *   NEXT
     * NEXT
    */

    double start = omp_get_wtime();

    end = ((n - 2) + 1) / 2;

    for (long i = 0; i <= end; i++)
    {
        if (composites[i])
        {
            continue;
        }

#pragma omp parallel for num_threads(threads)
        for (long j = i + 1; j <= n - 2; j++)
        {
            if (composites[j])
            {
                continue;
            }

            if ((j + 2) % (i + 2) == 0)
            {
                composites[j] = true;
            }
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
        printf("Error: I/O.\n");

        return 1;
    }

    long x = 0;

    for (long i = 0; i <= n - 2; i++)
    {
        if (composites[i])
        {
            continue;
        }

        x++;

        fprintf(stream, "%ld ", i + 2);
    }

    fclose(stream);
    free(composites);
    printf("%ld\n", x);

    return 0;
}
