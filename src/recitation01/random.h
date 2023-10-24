#include <stdlib.h>

/**
 * Generates a pseudorandom number greater than a given value.
 *
 * @param value The exclusive lower bound of the result.
 * @return A number greater than the given value.
 */
int rand_greater_than(int value)
{
    return (rand() % (RAND_MAX - value + 1)) + value;
}

/**
 * Determines the number of odd and even integers in a given range.
 *
 * @param minValue The inclusive lower bound of the range.
 * @param maxValue The exclusive upper bound of the range.
 * @param count    When this method returns, contains the number of integers in
 *                 the range.
 * @param odd      When this method returns, contains the number of odd
 *                 integers in the given range.
 * @param even     When this method returns, contains the number of even
 *                 integers in the given range.
 */
void count_odd_even(int minValue, int maxValue, int *count, int *odd, int *even)
{
    *count = maxValue - minValue;

    int maxRemainder = maxValue % 2;
    int minRemainder = minValue % 2;

    *odd = (*count + maxRemainder - minRemainder) / 2;
    *even = *count - *odd;
}
