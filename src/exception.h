#include <stdbool.h>

enum Exception
{
    EXCEPTION_ARGUMENT_OUT_OF_RANGE
};

typedef enum Exception *Exception;

void *throws(Exception exception, enum Exception value);
bool catches(Exception exception, enum Exception value);
