#include <stdio.h>
#include <string.h>

/**
 * Prints the binary representation of a byte to the standard output stream.
 * 
 * @param value the byte to print
*/
void print_in_binary(char value)
{
    static char b[17];
    
    b[0] = '\0';

    int z;

    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((value & z) == z) ? "1" : "0");
    }

    printf("%d in binary is %s\n", value, b);
}

/**
 * Prints a message indicating that a specified part of the program has
 * executed without error.
 * 
 * @param part the part number
*/
void part_completed(int part)
{
    printf("Tests for part%3d passed!\n", part);
}
