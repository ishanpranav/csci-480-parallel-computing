#include <errno.h>
#include <stdio.h>
#include "core.h"
#include "file.h"

FileStream file_create(String path, Exception exception)
{
    if (!path)
    {
        return throws(exception, EXCEPTION_ARGUMENT_NULL);
    }

    FileStream result = fopen(path, "w");

    if (!result)
    {
        switch (errno)
        {
        case EACCES:
            return throws(exception, EXCEPTION_UNAUTHORIZED_ACCESS);
        case ENAMETOOLONG:
            return throws(exception, EXCEPTION_PATH_TOO_LONG);
        case ENOENT:
            return throws(exception, EXCEPTION_DIRECTORY_NOT_FOUND);
        }
    }

    return result;
}
