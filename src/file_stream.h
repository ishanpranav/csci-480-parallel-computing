#include <stdio.h>

/** */
typedef FILE* FileStream;

void file_stream_close(FileStream instance)
{
    fclose(instance);
}
