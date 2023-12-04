#include <mpi.h>
#include <stdio.h>

/** Represents text as a zero-terminated sequence of characters. */
typedef char *String;

/**
 * Represents a function whose input is one double-precision floating-point
 * number and whose output is a double-precision floating-point number.
 */
typedef double (*DoubleDoubleFunc)(double value);

/**
 * Reads the properties of a trapezoid from the standard input stream and
 * broadcasts them to all communicators.
 *
 * @param rank the MPI communicator identifier.
 * @param size the number of MPI communicators.
 * @param a    when this method returns, contains the user-supplied left
 *             endpoint of the trapezoid. This parameter is passed
 *             uninitialized; any value originally supplied in `a` will be
 *             overwritten.
 * @param b    when this method returns, contains the user-supplied right
 *             endpoint of the trapezoid. This parameter is passed
 *             uninitialized; any value originally supplied in `b` will be
 *             overwritten.
 * @param n    when this method returns, contains the user-supplied number of
 *             trapezoids. This parameter is passed uninitialized; any value
 *             originally supplied in `n` will be overwritten.
 */
static void read(int rank, int size, double *a, double *b, int *n)
{
    if (rank == 0)
    {
        printf("Enter a, b, and n\n");
        scanf("%lf %lf %d", a, b, n);
    }

    MPI_Bcast(a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(n, 1, MPI_INT, 0, MPI_COMM_WORLD);
}

/**
 * Computes the square of the given value.
 *
 * @param x a real number.
 * @return The `y`-coordinate corresponding to the given `x`-coordinate for the
 *         function `y=x^2`.
 */
static double parabola(double x)
{
    return x * x;
}

/**
 * Approximates a definite integral using a trapezoidal Riemann sum.
 *
 * @param f  the function whose integral to approximate
 * @param a  the lower bound of the integration
 * @param b  the upper bound of the integration
 * @param dx the width of each trapezoid, or the horizontal change
 * @param n  the number of trapezoids to use in the approximation
 * @return An approximation of the integral of `f(x)` from `a` to `b` using `n`
 *         trapezoids, with each trapezoid having a width of `dx`.
 */
static double integrate(
    DoubleDoubleFunc f,
    double a,
    double b,
    int n,
    double dx)
{
    double result = (f(a) + f(b)) / 2.0;

    for (int i = 1; i < n; i++)
    {
        result += f(a + (i * dx));
    }

    return result * dx;
}

/**
 * The main entry point for the application.
 *
 * @param count the number of command-line arguments.
 * @param args  a collection of command-line arguments. The length of the
 *              collection is given by the `count` parameter.
 * @return An exit code. This value is always 0, indicating success.
 */
int main(int count, String args[])
{
    int rank;
    int size;
    int n;
    double a;
    double b;

    MPI_Init(&count, &args);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    read(rank, size, &a, &b, &n);

    int localN = n / size;
    double dx = (b - a) / n;
    double localA = a + (rank * localN * dx);
    double localB = localA + (localN * dx);
    double localIntegral = integrate(
        parabola,
        localA,
        localB,
        localN,
        dx);
    double integral;

    MPI_Reduce(
        &localIntegral,
        &integral,
        1,
        MPI_DOUBLE,
        MPI_SUM,
        0,
        MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf(
            "With n = %d trapezoids, our estimate\nof the integral from %f to %f is %.15e\n",
            n,
            a,
            b,
            integral);
    }

    MPI_Finalize();

    return 0;
}
