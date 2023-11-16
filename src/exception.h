enum Exception
{
    EXCEPTION_ARGUMENT_OUT_OF_RANGE
};

typedef enum Exception *Exception;

void *throw(Exception exception, enum Exception value);
