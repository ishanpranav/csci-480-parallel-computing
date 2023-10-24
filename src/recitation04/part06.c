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
    short a = 0b101010101;
    short mask = 0b111;

    print_in_binary((a & mask));
    assert((a & mask) == 0b101);
    part_completed(6);

    return 0;
}
