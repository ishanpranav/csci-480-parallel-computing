#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/** Represents text as a zero-terminated sequence of characters. */
typedef char *String;

/**
 * The main entry point for the application.
 *
 * @param count the number of command-line arguments.
 * @param args  a collection of command-line arguments. The length of the
 *              collection is given by the `count` parameter.
 * @return This value is 0, indicating success, or 1, indicating
 *         a usage error.
 */
int main(int count, String args[])
{
    if (count != 3)
    {
        fprintf(stderr, "usage: omppi <iterations> <block_size>\n");

        return 1;
    }

    int i;
    int n = atoi(args[1]);
    int blockSize = atoi(args[2]);
    double t0 = omp_get_wtime();
    int *durations = malloc(n * sizeof(int));

    srand(time(NULL));
    
    for (i = 0; i < n; i++)
    {
        durations[i] = (rand() % 4) + 1;
    }

    double t1;
    double t2;

#pragma omp parallel shared(n) private(i, t1, t2) num_threads(4)
    {
#pragma omp for schedule(static, blockSize)
        for (i = 0; i < n; i++)
        {
            t1 = omp_get_wtime();

            sleep(durations[i]);

            t2 = omp_get_wtime();

            printf(
                "Iteration %d: Thread %d, started %e, duration %e\n",
                i,
                omp_get_thread_num(),
                t1 - t0,
                t2 - t1);
        }
    }

    printf("CPU time used: %.2f sec\n", omp_get_wtime() - t0);

    return 0;
}
