#include <stdio.h>
#include "../core.h"

/**
 *
 * @param n
 * @param divisor
 * @return
 */
static int lab1sequential_count_factors(int n, int divisor)
{
    int result = 0;

    for (int i = 2; i <= n; i++)
    {
        if (i % divisor == 0)
        {
            result++;
        }
    }

    return result;
}

/**
 * The main entry point for the application.
 *
 * @param count     the number of command-line arguments.
 * @param arguments a collection of command-line arguments. The length of the
 *                  collection is given by the `count` parameter.
 * @return An exit code. This value is always 0, indicating success.
 */
int main(int count, StringArray arguments)
{
    int n;

    scanf("%d", &n);
    printf("%d: %d\n%d: %d\n%d: %d\n%d: %d\n%d: %d",
           2, lab1sequential_count_factors(n, 2),
           3, lab1sequential_count_factors(n, 3),
           5, lab1sequential_count_factors(n, 5),
           7, lab1sequential_count_factors(n, 7),
           13, lab1sequential_count_factors(n, 13));

    return 0;
}
