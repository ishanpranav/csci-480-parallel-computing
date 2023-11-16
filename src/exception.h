#ifndef SYSTEM__EXCEPTION_H
#define SYSTEM__EXCEPTION_H
#include <stdbool.h>

enum Exception
{
    EXCEPTION_NONE,
    EXCEPTION_ARGUMENT_OUT_OF_RANGE,
    EXCEPTION_ARGUMENT_NULL,
    EXCEPTION_DIRECTORY_NOT_FOUND,
    EXCEPTION_PATH_TOO_LONG,
    EXCEPTION_UNAUTHORIZED_ACCESS,
    EXCEPTION = 0
};

typedef enum Exception *Exception;

void *throws(Exception exception, enum Exception value);
bool catches(Exception exception, enum Exception value);

#endif
