/** Represents text as a sequence of zero-terminated ASCII characters. */
typedef char *String;

/** Represents a two-dimensional array of signed integers. */
typedef int* IntArray;

/** Represents a two-dimensional array of signed long integers. */
typedef long* LongArray;

/**
 * Initializes a new array of signed integers with the specified `length`.
 * 
 * @param length the size of the array to create.
 * @return A new one-dimensional array of signed integers with the specified
 *         length.
*/
IntArray int_array(int length);

/**
 * Initializes a new array of signed long integers with the specified `length`.
 * 
 * @param length the size of the array to create.
 * @return A new one-dimensional array of signed long integers with the
 *         specified length.
*/
LongArray long_array(int length);

/**
 * Returns the largest integral value less than or equal to the specified
 * double-precision floating-point number.
 * 
 * @param value a double-precision floating-point number.
 * @return The largest integral value less than or equal to `value`. If `value`
 *         is equal to `NAN`, `-INFINITY`, or `INFINITY`, that value is
 *         returned.
*/
double math_floor(double value)
{
    return floor(value);
}
