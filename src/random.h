#include "exception.h"

/**
 * Represents a pseudo-random number generator, which is an algorithm that
 * produces a sequence of numbers that meet certain statistical requirements
 * for randomness.
 */
typedef unsigned int *Random;

/**
 * Initializes a new instance of the `Random` class using a default seed value.
 * 
 * @return A new instance of the `Random` class.
*/
Random random();

/**
 * Returns a random integer that is within a specified range.
 * 
 * @param instance  the `Random` instance.
 * @param minValue  the inclusive lower bound of the random number returned.
 * @param maxValue  the exclusive upper bound of the random number returned.
 *                  `maxValue` must be greater than or equal to `minValue`.
 * @param exception `EXCEPTION_ARGUMENT_OUT_OF_RANGE` if `minValue` is greater
 *                  than `maxValue`.
 * @return A 32-bit signed integer greater than or equal to `minValue` and less
 *         than `maxValue`; that is, the range of return values includes
 *         `minValue` but not maxValue. If `minValue` equals `maxValue`,
 *         `minValue` is returned.
*/
int random_next(
    Random instance,
    int minValue,
    int maxValue, 
    Exception exception);
