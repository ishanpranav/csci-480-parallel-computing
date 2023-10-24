#include <stdio.h>
#include <assert.h>
#include "util.h"

/**
 * The main entry point for the application.
 *
 * @return An exit code. This value is 0 if all assertions succeed.
 */
int main()
{
    assert((0b1010 ^ 0b1111) == 0b0101);
    part_completed(9);

    return 0;
}
