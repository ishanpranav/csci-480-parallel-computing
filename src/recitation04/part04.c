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
    char bits = 0b1010;

    assert((0b0000 ^ bits) == 0b1010);
    assert((0b0111 ^ bits) == 0b1101);
    assert((0b0101 ^ bits) == 0b1111);
    part_completed(4);

    return 0;
}
