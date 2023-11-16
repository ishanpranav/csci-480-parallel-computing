#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../core.h"
#include "../file.h"
#include "../file_stream.h"

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

    if (n < 2 || n > 10000000)
    {
        printf("<n> must be a positive number between 2 and 10000000.\n");

        return 1;
    }

    int threads = atoi(args[2]);

    if (threads < 0)
    {
        printf("<threads> must be a positive number.\n");
    }

    LongArray values = long_array(n - 1);

    for (int i = 2; i <= n; i++)
    {
        values[i - 2] = i;
    }

    int j = 2;

    while (j <= math_floor((n + 1) / 2))
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

    char buffer[13];

    sprintf(buffer, "%ld.txt", n);

    Exception exception = NULL;
    FileStream stream = file_create(buffer, exception);

    if (catches(exception, EXCEPTION))
    {
        perror(NULL);

        return 1;
    }

    for (int i = 0; i < n - 1; i++)
    {
        if (values[i])
        {
            fprintf(stream, "%ld ", values[i]);
        }
    }

    file_stream_dispose(stream);
}
