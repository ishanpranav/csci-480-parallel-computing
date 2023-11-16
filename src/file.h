#include <stdio.h>
#include "file_stream.h"

/** */
FileStream file_create(String fileName)
{
    return fopen(fileName, "w");
}