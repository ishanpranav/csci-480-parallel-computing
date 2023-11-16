#include <stdio.h>
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
    const int LAB1_RESULT_COUNT = 5;

    int n;
    int results[LAB1_RESULT_COUNT];

    scanf("%d", &n);
    lab1_count_factors(2, n, LAB1_RESULT_COUNT, results, 2, 3, 5, 7, 13);
    lab1_print_factors(LAB1_RESULT_COUNT, results, 2, 3, 5, 7, 13);

    return 0;
}
