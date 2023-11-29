#include "exception.h"

void throws(Exception exception, enum Exception value)
{
    if (exception)
    {
        *exception = value;
    }
}

bool catches(Exception exception, enum Exception value)
{
    if (!exception)
    {
        return false;
    }

    if (!value)
    {
        return *exception;
    }

    return *exception == value;
}
