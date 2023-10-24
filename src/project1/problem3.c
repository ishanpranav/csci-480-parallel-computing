// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav. All rights reserved. 
// Licensed under the MIT License. 

#include <stdbool.h>
#include <stdio.h>

/**
 * The main entry point for the application.
 *
 * @return An exit code. This value is always 0, indicating success.
 */
int main()
{
    int n;

    // Scan values into N until N is 0

    while (scanf("%d", &n) && n)
    {
        int j = 0;
        int an = 0;
        int bn = 0;
        bool isA = 1;

        // Destructively iterate over the bits of N (right-shift until N is 0)

        while (n)
        {
            // If N is even (the least significant bit is 1)

            if (n & 1)
            {
                if (isA)
                {
                    // Add a one at the j-th bit of 'an'

                    an |= 1 << j;
                    isA = false;
                }
                else
                {
                    // Add a one at the j-th bit of 'bn'

                    bn |= 1 << j;
                    isA = true;
                }
            }

            j++;
            n >>= 1;
        }

        printf("%d %d\n", an, bn);
    }

    return 0;
}
