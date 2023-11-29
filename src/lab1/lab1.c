#include <stdarg.h>
#include <stdio.h>
#include "lab1.h"

void lab1_count_factors(long min, long max, long count, long results[], ...)
{
    for (long j = 0; j < count; j++)
    {
        results[j] = 0;
    }

    va_list params;

    for (long i = min; i <= max; i++)
    {
        va_start(params, results);

        for (long j = 0; j < count; j++)
        {
            if (i % va_arg(params, long) == 0)
            {
                results[j]++;
            }
        }

        va_end(params);
    }
}

void lab1_print_factors(long count, long results[], ...)
{
    va_list params;

    va_start(params, results);

    for (long j = 0; j < count; j++)
    {
        printf("%ld: %ld\n", va_arg(params, long), results[j]);
    }

    va_end(params);
}
