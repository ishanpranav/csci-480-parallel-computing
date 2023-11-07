#include <stdarg.h>
#include "lab1.h"

void lab1_count_factors(int offset, int length, int count, int results[], ...)
{
    for (int j = 0; j < count; j++)
    {
        results[j] = 0;
    }

    va_list params;

    for (int i = offset; i <= offset + length; i++)
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
