#include "exception.h"

void *throws(Exception * exception, Exception value)
{
    if (exception)
    {
        *exception = value;
    }

    return 0;
}
