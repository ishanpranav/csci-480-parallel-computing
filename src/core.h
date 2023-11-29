#ifndef SYSTEM_H
#define SYSTEM_H
#define ARRAY_MAX_LENGTH SIZE_MAX

/** Represents text as a sequence of zero-terminated ASCII characters. */
typedef char *String;

/** Represents a two-dimensional array of signed integers. */
typedef int* IntArray;

/**
 * Initializes a new array of signed integers with the specified `length`.
 * 
 * @param length the size of the array to create.
 * @return A new one-dimensional array of signed integers with the specified
 *         length.
*/
IntArray int_array(int length);

/**
 * Returns the largest integral value less than or equal to the specified
 * double-precision floating-point number.
 * 
 * @param value a double-precision floating-point number.
 * @return The largest integral value less than or equal to `value`. If `value`
 *         is equal to `NAN`, `-INFINITY`, or `INFINITY`, that value is
 *         returned.
*/
double math_floor(double value);

#endif