#include <stdio.h>
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
    const int RESULTS_COUNT = 5;

    int n;
    int results[RESULTS_COUNT];

    scanf("%d", &n);
    lab1_count_factors(2, n - 2, RESULTS_COUNT, results, 2, 3, 5, 7, 13);
    printf("%d: %d\n%d: %d\n%d: %d\n%d: %d\n%d: %d\n",
        2, results[0],
        3, results[1],
        5, results[2],
        7, results[3],
        13, results[4]);

    return 0;
}
