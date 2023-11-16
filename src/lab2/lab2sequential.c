#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../core.h"
#include "../int_array.h"

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
        printf("Usage: lab2sequential <n> <threads>\n");

        return 1;
    }

    long n = strtol(args[1], NULL, 10);

    if (n < 2)
    {
        printf("<n> must be a positive number greater than 2.\n");

        return 1;
    }

    int threads = atoi(args[2]);

    if (threads < 0)
    {
        printf("<threads> must be a positive number.\n");
    }

    IntArray values = int_array(n - 1);

    for (int i = 2; i <= n; i++)
    {
        values[i - 2] = i;
    }

    int j = 2;

    while (j <= floor((n + 1) / 2))
    {
        for (int i = j + 1; i <= n; i++)
        {
            if (i % j == 0)
            {
                values[i - 2] = 0;
            }
        }

        for (int i = j + 1; i <= n; i++)
        {
            if (values[i - 2])
            {
                j = i;

                break;
            }
        }
    }

    for (int i = 0; i < n - 1; i++)
    {
        if (values[i])
        {
            printf("%d\n", values[i]);
        }
    }
}
