#include <stdio.h>

/** Provides a stream for a file, supporting read and write operations. */
typedef FILE* FileStream;

/**
 * Releases the resources used by the `FileStream`.
 * 
 * @param instance the `FileStream` instance.
*/
void file_stream_dispose(FileStream instance);
