#include <stdlib.h>
#include "double_array.h"

DoubleArray double_array(int length)
{
    return malloc(sizeof(double) * length);
}

DoubleMatrix double_matrix(int x, int y)
{
    return malloc(sizeof(double) * x * y);
}
