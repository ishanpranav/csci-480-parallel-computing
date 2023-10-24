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
    int mask = 0b11;

    assert(((0b00001011010111 >> 2) & mask) == 0b01);
    assert(((0b11001001001101 >> 2) & mask) == 0b11);
    part_completed(8);

    return 0;
}
