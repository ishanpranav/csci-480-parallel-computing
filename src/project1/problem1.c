// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav. All rights reserved. 
// Licensed under the MIT License. 

#include <stdio.h>

/* Specifies an invalid date. */
#define INVALID -1

/* Specifies the message displayed when parsing fails. */
#define INVALID_MESSAGE "INVALID\n"

/**
 * Converts integers representing a date/time into a single compressed integer.
 *
 * @param month  The month, an integer between 1 and 12 (inclusive).
 * @param day    The date, an integer between 1 and 31 (inclusive).
 * @param hour   The hour, expressed in 24-hour time. This value must be an
 *		        integer between 0 and 23 (inclusive).
 * @param minute The minute, an integer between 0 and 59 (inclusive).
 * @param second The second, an integer between 0 and 59 (inclusive).
 * @return -1 if any argument is out of range; otherwise, a 32-bit integer
 *	       that represents the date/time value.
 *
 * The four least significant bits (bits 0-3 in little-endian notation)
 * represent the "ones" digit of the second. The next three bits (4-6) represent
 * the "tens" digit of the second. Bits 7-10 and 11-13 represent the "ones" and
 * "tens" digits of the minutes, respectively. Bits 14-17 represent the "ones"
 * digit of the hour. Bits 18 and 19 represent the "tens" digit of the hour.
 * Bits 20-23 represent the "ones" digit of the date. Bits 24 and 25 represent
 * the "tens" digit of the date. Bits 26-29 represent the "ones" digit of the
 * month, and bit 30 represents the tens digit of the month. Finally, bit 31 is
 * always 0 if the conversion was successful.
 */
int convert_date(int month, int day, int hour, int minute, int second)
{
    // Guard against arguments out of range

    if (month < 1 || month > 12 ||
        day < 1 || day > 31 ||
        hour < 0 || hour > 23 ||
        minute < 0 || minute > 59 ||
        second < 0 || second > 59)
    {
        return INVALID;
    }

    // Shift each value into the correct position (little endian)

    return (second % 10) | ((second / 10) << 4) |
           ((minute % 10) << 7) | ((minute / 10) << 11) |
           ((hour % 10) << 14) | ((hour / 10) << 18) |
           ((day % 10) << 20) | ((day / 10) << 24) |
           ((month % 10) << 26) | ((month / 10) << 30);
}

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

    int i;

    for (i = 0; i < n; i++)
    {
        int month;
        int day;
        int hour;
        int minute;
        int second;

        // Scan values in the form MM/dd hh:mm:ss

        if (!scanf("%d/%d %d:%d:%d", &month, &day, &hour, &minute, &second))
        {
            printf(INVALID_MESSAGE);

            continue;
        }

        int value = convert_date(month, day, hour, minute, second);

        // Guard against invalid results

        if (value == INVALID)
        {
            printf(INVALID_MESSAGE);

            continue;
        }

        // Print the converted date as a decimal integer

        printf("%d\n", value);
    }

    return 0;
}
