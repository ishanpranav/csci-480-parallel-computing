#include <stdio.h>
#include <assert.h>
#include "util.h"

void part_completed(int);

/**
 * The main entry point for the application.
 * 
 * @return An exit code. This value is 0 if all assertions succeed. 
 */
int main()
{
    char bits = 0b1000;

    assert((0 | bits) == 0b1000);
    assert((5 | bits) == 0b1101);
    assert((7 | bits) == 0b1111);
    part_completed(3);

    return 0;
}
