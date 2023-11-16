#include <stdlib.h>
#include <time.h>
#include "random.h"

Random random()
{
    Random result = malloc(sizeof(unsigned int));

    *result = time(NULL);

    return result;
}

int random_next(
    Random instance,
    int minValue,
    int maxValue,
    Exception exception)
{
    if (minValue > maxValue)
    {
        return throws(exception, EXCEPTION_ARGUMENT_OUT_OF_RANGE);
    }

    return (rand_r(instance) % maxValue) + minValue;
}
