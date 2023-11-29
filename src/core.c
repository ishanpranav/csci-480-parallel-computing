#include <math.h>
#include <stdlib.h>
#include "core.h"

IntArray int_array(int length)
{
    return malloc(sizeof(int) * length);
}

double math_floor(double value)
{
    return floor(value);
}
