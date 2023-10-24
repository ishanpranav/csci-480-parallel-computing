#include <stdio.h>
#include <time.h>
#include "random.h"

/**
 * The main entry point for the application.
 *
 * @return An exit code. This value is always 0, indicating success.
 */
int main()
{
    srand((int)time(NULL));

    int i;

    for (i = 1; i < 100; i++)
    {
        int count;
        int odd;
        int even;
        int minValue = rand_greater_than(0);
        int maxValue = rand_greater_than(minValue);

        count_odd_even(minValue, maxValue, &count, &odd, &even);
        printf("Range: %d\t-\t%d\tCount: %d\tOdd: %d\tEven: %d\n", minValue, maxValue - 1, count, odd, even);
    }

    return 0;
}
