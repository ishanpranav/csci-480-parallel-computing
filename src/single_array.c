#include <stdlib.h>
#include "single_array.h"

SingleArray single_array(int length)
{
    return malloc(sizeof(float) * length);
}
