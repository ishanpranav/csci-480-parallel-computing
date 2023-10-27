/** Represents an array of double-precision floating-point numbers. */
typedef float *DoubleArray;

/**
 * Represents a two-dimensional array of double-precision floating-point
 * numbers.
 */
typedef float *DoubleMatrix;

/**
 * Initializes a new array of double-precision floating-point numbers with the
 * specified `length`.
 * 
 * @param length the size of the array to create.
 * @return A new one-dimensional array of double-precision floating-point
 *         numbers with the specified length.
*/
DoubleArray double_array(int length);

/**
 * Initializes a new two-dimensional array of double-precision floating-point
 * numbers with the specified `length`.
 *
 * @param x the size of the first dimension of the array to create.
 * @param y the size of the second dimension of the array to create.
 * @return A new two-dimensional array of double-precision floating-point
 *         numbers with the specified `x` and `y` dimension sizes.
 */
DoubleMatrix double_matrix(int x, int y);
