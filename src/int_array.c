#include <stdlib.h>
#include "int_array.h"

IntArray int_array(int length)
{
    return malloc(sizeof(int) * length);
}
