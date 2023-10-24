#include <stdlib.h>
#include "single_array.h"

SingleArray single_array(int length)
{
    SingleArray result = malloc(sizeof *result * length);

    return result;
}
