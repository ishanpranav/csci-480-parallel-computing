// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav. All rights reserved. 
// Licensed under the MIT License. 

#include <stdio.h>

/**
 * The main entry point for the application.
 *
 * @return 1 if the application did not receive a properly formatted number of
 *         inputs N from the standard input stream; otherwise, 0.
 */
int main()
{
    int n;

    if (!scanf("%d", &n))
    {
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        int r;
        int g;
        int b;

        // Scan values in the form R, G, B

        if (!scanf("%d, %d, %d", &r, &g, &b) ||
            r < 0 || r > 255 ||
            g < 0 || g > 255 || 
            b < 0 || b > 255)
        {
            printf("INVALID\n");

            continue;
        }
                   
        // Print the color as a single hexadecimal integer preceded by a #
        
        printf("#%02x%02x%02x\n", r, g, b);
    }

    return 0;
}
