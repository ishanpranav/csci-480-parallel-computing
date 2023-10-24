// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav. All rights reserved. 
// Licensed under the MIT License. 

#ifndef FLOAT_H_
#define FLOAT_H_

/**
 * Determines if the given value uses special-value encoding.
 *
 * This function assumes that the int and float data types have the same size.
 *
 * @param value the floating-point number to test
 * @return A non-zero integer if the given value uses special-value encoding;
 *         otherwise, false.
 */
int is_special(float value);

/**
 * Computes the mantissa of a given IEEE single-precision floating-point
 * number.
 *
 * This function assumes that the int and float data types have the same size.
 *
 * @param value the floating-point number from which to extract the mantissa
 * @return The mantissa of the given value, 0 if the given value is negative
 *         infinity or positive infinity, or any other non-zero value if the
 *         given value is not a number.
 */
float get_M(float value);

/**
 * Computes the sign of the given IEEE single-precision floating-point number.
 *
 * This function assumes that the int and float data types have the same size.
 *
 * @param value the floating-point number from which to extract the sign
 * @return -1 if the given value is negative; otherwise 1.
 */
int get_s(float value);

/**
 * Computes the exponent of the given IEEE single-precision floating-point
 * number.
 *
 * This function assumes that the int and float data types have the same size.
 *
 * @param value the floating-point number from which to extract the exponent
 * @return The exponent of the given value.
 */
int get_E(float value);

#endif
