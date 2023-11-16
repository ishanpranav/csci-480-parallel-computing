#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "int_array.h"
#include "random.h"

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
        fprintf(stderr, "usage: omppi <iterations> <block size>\n");

        return 1;
    }

    int n = atoi(args[1]);
    int blockSize = atoi(args[2]);
    double t0 = omp_get_wtime();
    IntArray durations = int_array(n);
    Random randomInstance = random();
    
    for (int i = 0; i < n; i++)
    {
        durations[i] = random_next(randomInstance, 1, 5);
    }

    return 0;
}
