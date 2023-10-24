#include <stdio.h>
#include <assert.h>
#include "util.h"

/**
 * Performs a binary left shift operation.
 * 
 * @param value the value to shift
 * @param shift the number of steps
 * 
*/
int left_shift(int value, int shift)
{
    return value << shift;
}

/**
 * Performs a binary right shift operation.
 * 
 * @param value the value to shift
 * @param shift the number of steps
*/
int right_shift(int value, int shift)
{
    return value >> shift;
}

/**
 * The main entry point for the application.
 * 
 * @return An exit code. This value is 0 if all assertions succeed. 
 */
int main()
{
    assert(left_shift(1, 2) == 4);
    assert(left_shift(5, 3) == 40);
    assert(left_shift(4, 3) == 32);
    assert(right_shift(20, 3) == 2);
    assert(right_shift(2, 2) == 0);
    assert(right_shift(16, 3) == 2);
    assert(left_shift(0b00000001, 2) == 4);
    assert(right_shift(0b01000000, 3) == 8);
    print_in_binary(12);
    print_in_binary(0b10000000);
    print_in_binary(right_shift(0b10000000, 1));
    assert(right_shift(128, 1) == 0b1000000);
    part_completed(1);

    return 0;
}
