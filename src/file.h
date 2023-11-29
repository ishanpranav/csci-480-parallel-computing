#include <stdio.h>
#include "core.h"
#include "exception.h"
#include "file_stream.h"

/**
 * Creates or overwrites a file in the specified path.
 * 
 * @param path      the path and name of the file to create.
 * @param exception the exception.
 * @return A `FileStream` that provides read/write access to the file specified
 *         in `path`.
*/
FileStream file_create(String path, Exception exception);
