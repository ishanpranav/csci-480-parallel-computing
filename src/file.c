#include <errno.h>
#include <stdio.h>
#include "file.h"

FileStream file_create(String path, Exception exception)
{
    if (!path)
    {
        throws(exception, EXCEPTION_ARGUMENT_NULL);

        return NULL;
    }

    FileStream result = fopen(path, "w");

    if (!result)
    {
        switch (errno)
        {
        case EACCES:
            throws(exception, EXCEPTION_UNAUTHORIZED_ACCESS);
            return NULL;

        case ENAMETOOLONG:
            throws(exception, EXCEPTION_PATH_TOO_LONG);
            return NULL;

        case ENOENT:
            throws(exception, EXCEPTION_DIRECTORY_NOT_FOUND);
            return NULL;
        }
    }

    return result;
}
