#include <stdio.h>
#include <assert.h>
#include "util.h"

/**
 * Performs the "bit wisdom" transformation on a given number. All bits except
 * the bits in the "ones," "twos," "fours," and "eights" places are set to 0.
 * The "ones" and "twos" bits are inverted. The "fours" and "eights" bits are
 * set to 1.
 * 
 * @param value the input bit string
 * @return The transformed bit string.
*/
int bit_wisdom(int value)
{
    return ((value & 0b1111) ^ (0b11)) | 0b1100;
}

/**
 * The main entry point for the application.
 *
 * @return An exit code. This value is 0 if all assertions succeed.
 */
int main()
{
    assert(bit_wisdom(0b11111111) == 0b00001100);
    assert(bit_wisdom(0b00000000) == 0b00001111);
    assert(bit_wisdom(0b10101010) == 0b00001101);
    assert(bit_wisdom(0b01010101) == 0b00001110);
    part_completed(11);

    return 0;
}
