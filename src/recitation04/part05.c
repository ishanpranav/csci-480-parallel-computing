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
    print_in_binary(~0b1111);
    print_in_binary(~0b0000);
    print_in_binary(2);
    print_in_binary(~-2);
    print_in_binary(4);
    print_in_binary(~-4);

    char x = 0b11111110;
    char y = 0;

    assert(~1 == x);
    assert(~-1 == y);

    part_completed(5);

    return 0;
}
