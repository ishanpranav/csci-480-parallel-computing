#include <stdlib.h>
#include <time.h>
#include "random.h"

Random random_get_shared()
{
    return NULL;
}

int random_next(
    Random instance,
    int minValue,
    int maxValue,
    Exception exception)
{
    if (minValue > maxValue)
    {
        throws(exception, EXCEPTION_ARGUMENT_OUT_OF_RANGE);

        return 0;
    }

    return (rand() % (maxValue - minValue)) + minValue;
}
