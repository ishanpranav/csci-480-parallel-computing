#include "file_stream.h"
#include <stdio.h>

void file_stream_dispose(FileStream instance)
{
    fclose(instance);
}
