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
    short a = 0b1010000;
    short mask = 0b111;
    
    assert((a | mask) == 0b1010111);
    assert((a | mask) == 87);
    part_completed(7);

    return 0;
}
