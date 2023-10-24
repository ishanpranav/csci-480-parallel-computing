#include <stdio.h>
#include <assert.h>
#include "util.h"

/**
 * Returns the given number with bit at the given index inverted (where the
 * "ones" bit being the zero-th bit).
 *
 * @param index the bit number in zero-indexed little-endian notation.
 * @param value the input bit string
 * @return The transformed bit string.
 */
int flip_bit(int index, int value)
{
    return value ^ (1 << index);
}

/**
 * The main entry point for the application.
 *
 * @return An exit code. This value is 0 if all assertions succeed.
 */
int main()
{
    assert(flip_bit(0, 0) == 1);
    assert(flip_bit(1, 0) == 2);
    assert(flip_bit(3, 10) == 2);
    assert(flip_bit(3, 3) == 11);
    assert(flip_bit(4, 0) == 16);
    part_completed(10);

    return 0;
}
