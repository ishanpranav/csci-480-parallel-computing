#include "exception.h"

void *throws(Exception exception, enum Exception value)
{
    if (exception)
    {
        *exception = value;
    }

    return 0;
}

bool catches(Exception exception, enum Exception value)
{
    return *exception == value;
}
