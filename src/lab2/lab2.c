#include <stdlib.h>
#include "../file.h"
#include "lab2.h"

void lab2_write(long n, long values[])
{
    char buffer[13];

    sprintf(buffer, "%ld.txt", n);

    Exception exception = NULL;
    FileStream stream = file_create(buffer, exception);

    if (catches(exception, EXCEPTION))
    {
        perror(NULL);

        return;
    }

    long count = 0;

    for (long i = 0; i <= n - 2; i++)
    {
        if (values[i] != 1)
        {
            count++;

            fprintf(stream, "%ld ", values[i]);
        }
    }

    file_stream_dispose(stream);
    printf("%ld\n", count);
}
