#include <stdarg.h>
#include <stdio.h>
#include "lab1.h"

void lab1_count_factors(int min, int max, int count, int results[], ...)
{
    for (int j = 0; j < count; j++)
    {
        results[j] = 0;
    }

    va_list params;

    for (int i = min; i <= max; i++)
    {
        va_start(params, results);

        for (int j = 0; j < count; j++)
        {
            if (i % va_arg(params, int) == 0)
            {
                results[j]++;
            }
        }

        va_end(params);
    }
}

void lab1_print_factors(int count, int results[], ...)
{
    va_list params;

    va_start(params, results);

    for (int j = 0; j < count; j++)
    {
        printf("%d: %d\n", va_arg(params, int), results[j]);
    }

    va_end(params);
}
