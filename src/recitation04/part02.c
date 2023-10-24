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
    char bits = 0b1111;
    
    assert((15 & bits) == 0b1111);
    assert((1 & bits) == 0b0001);
    assert((5 & bits) == 0b0101);
    part_completed(2);

    return 0;
}
