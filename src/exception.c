#include "exception.h"

void *throws(Exception exception, enum Exception value)
{
    if (exception)
    {
        *exception = value;
    }
}

bool catches(Exception exception, enum Exception value)
{
    return *exception == value;
}
