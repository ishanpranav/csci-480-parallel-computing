// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav. All rights reserved.
// Licensed under the MIT License.

#include <stdio.h>
#include <stdlib.h>

/** Represents text as a zero-terminated sequence of characters. */
typedef char *String;

/**
 * The main entry point for the application.
 *
 * @param count the number of command-line arguments.
 * @param args  a collection of command-line arguments. The length of the
 *              collection is given by the `count` parameter. By convention,
 *              the first argument is the name of the program.
 * @return An exit code. This value is 0, indicating success, or 1, indicating
 *         a usage or system error.
 */
int main(int count, String args[])
{
    if (count != 3)
    {
        printf("Usage: divisible <n> <factor>\n");

        return 1;
    }

    // Since `n` can be up to 10,000,000 we need at least 32 bits (`long`).

    long n = atol(args[1]);

    if (n < 2 || n > 10000000)
    {
        printf("<n> must be a positive number between 2 and 10,000,000.\n");

        return 1;
    }

    long count = 0;
    long factor = atol(args[2]);
    int blocks = 0;
    int threadsPerBlock = 0;

    printf(
        "There are %d numbers divisible by %d in the range [2, %d].\nNumber of blocks used is %d\nNumber of threads per block is %d",
        count,
        factor,
        n,
        blocks,
        threadsPerBlock);

    return 0;
}
