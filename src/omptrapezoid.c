#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "double_double_func.h"

/**
 * Approximates a definite integral using a trapezoidal Riemann sum.
 *
 * @param f       the function whose integral to approximate
 * @param a       the lower bound of the integration
 * @param b       the upper bound of the integration
 * @param n       the number of trapezoids to use in the approximation
 * @param threads the number of threads
 * @return An approximation of the integral of `f(x)` from `a` to `b` using `n`
 *         trapezoids, with each trapezoid having a width of `dx`.
 */
static double omptrapezoid_integrate(
    DoubleDoubleFunc f,
    double a,
    double b,
    int n,
    int threads)
{
    double dx = (b - a) / n;
    double result = (f(b) - f(a)) / 2.0;

#pragma omp parallel for num_threads(threads) reduction(+ : result)
    for (int i = 1; i < n; i++)
    {
        result += f(a + (i * dx));
    }

    return result * dx;
}

/**
 * Computes the square of the given value.
 *
 * @param x a real number.
 * @return The `y`-coordinate corresponding to the given `x`-coordinate for the
 *         function `y=x^2`.
 */
static double omptrapezoid_parabola(double x)
{
    return x * x;
}

/**
 * The main entry point for the application.
 *
 * @param count the number of command-line arguments.
 * @param args  a collection of command-line arguments. The length of the
 *              collection is given by the `count` parameter.
 * @return This value is 0, indicating success, or 1, indicating
 *         a usage error.
 */
int main(int count, String args[])
{
    if (count != 2)
    {
        fprintf(stderr, "usage: omptrapezoid <number of threads>\n");

        return 1;
    }

    int threads = atoi(args[1]);
    int n;
    double a;
    double b;

    printf("Enter a, b, and n\n");
    scanf("%lf %lf %d", &a, &b, &n);
    printf("With n = %d trapezoids, our estimate\nof the integral from %f to %f is %.15e\n",
           n,
           a,
           b,
           omptrapezoid_integrate(omptrapezoid_parabola, a, b, n, threads));

    return 0;
}
