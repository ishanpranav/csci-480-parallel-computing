#include "core.h"
#include "double_array.h"
#include <mpi.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Terminates the program if a success condition is not met.
 *
 * @param localOk true if the success condition has been met; otherwise,
 *                false.
 * @param source  the name of the source function that raised the assertion.
 * @param message the error message associated with a failure condition.
 * @param comm    the communicator.
 */
static void mpimatrix_assert(
    bool localOk,
    String source,
    String message,
    MPI_Comm comm)
{
    bool ok;

    MPI_Allreduce(&localOk, &ok, 1, MPI_C_BOOL, MPI_MIN, comm);

    if (!ok)
    {
        int rank;

        MPI_Comm_rank(comm, &rank);

        if (rank == 0)
        {
            fprintf(stderr, "Proc %d > In %s, %s\n", rank, source, message);
            fflush(stderr);
        }

        MPI_Finalize();
        exit(1);
    }
}

/**
 * Reads user-specified dimensions from the standard input stream.
 *
 * @param m      when this method returns, contains the user-supplied number of
 *               rows in the matrix. This parameter is passed uninitialized;
 *               any value originally supplied in `m` will be overwritten.
 * @param n      when this method returns, contains the user-supplied number of
 *               columns in the matrix. This parameter is passed uninitialized;
 *               any value originally supplied in `n` will be overwritten.
 * @param rank   the communicator identifier.
 * @param size   the number of communicators.
 * @param comm   the communicator.
 */
static void mpimatrix_read(
    int rank,
    int size,
    MPI_Comm comm,
    int *m,
    int *n)
{
    if (rank == 0)
    {
        printf("Enter the number of rows\n");
        scanf("%d", m);
        printf("Enter the number of columns\n");
        scanf("%d", n);
    }

    MPI_Bcast(m, 1, MPI_INT, 0, comm);
    MPI_Bcast(n, 1, MPI_INT, 0, comm);
    mpimatrix_assert(
        *m <= 0 || *n <= 0 || *m % size != 0 || *n % size != 0,
        "mpimatrix_read",
        "m and n must be positive and evenly divisible by size",
        comm);
}

/**
 * Reads a user-specified matrix from the standard input stream.
 *
 * @param prompt      the user-friendly name of the matrix.
 * @param localMatrix the local matrix.
 * @param m           the number of rows in the matrix.
 * @param localM      the local number of rows in the matrix.
 * @param n           the number of columns in the matrix.
 * @param rank        the communicator identifier.
 * @param comm        the communicator.
 */
static void mpimatrix_read_matrix(
    String prompt,
    DoubleMatrix localMatrix,
    int m,
    int localM,
    int n,
    int rank,
    MPI_Comm comm)
{
    DoubleMatrix matrix;

    if (rank == 0)
    {
        matrix = double_matrix(m, n);

        mpimatrix_assert(
            matrix,
            "mpimatrix_read_matrix",
            "Can't allocate temporary matrix",
            comm);
        printf("Enter the matrix %s\n", prompt);

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                scanf("%lf", &matrix[i * n + j]);
            }
        }
    }
    else
    {
        matrix = NULL;
    }

    MPI_Scatter(
        matrix,
        localM * n,
        MPI_DOUBLE,
        localMatrix,
        localM * n,
        MPI_DOUBLE,
        0,
        comm);

    if (matrix)
    {
        free(matrix);
    }
}

/**
 * Reads a user-specified vector from the standard input stream.
 *
 * @param prompt      the user-friendly name of the vector.
 * @param localVector the local vector.
 * @param n           the length of the vector.
 * @param localN      the local length of the vector.
 * @param rank        the communicator identifier.
 * @param comm        the communicator.
 */
static void mpimatrix_read_vector(
    String prompt,
    DoubleArray localVector,
    int n,
    int localN,
    int rank,
    MPI_Comm comm)
{
    DoubleArray vector;

    if (rank == 0)
    {
        vector = double_array(n);

        mpimatrix_assert(
            vector,
            "mpimatrix_read_vector",
            "Can't allocate temporary vector",
            comm);
        printf("Enter the vector %s\n", prompt);

        for (int i = 0; i < n; i++)
        {
            scanf("%lf", &vector[i]);
        }
    }
    else
    {
        vector = NULL;
    }

    MPI_Scatter(
        vector,
        localN,
        MPI_DOUBLE,
        localVector,
        localN,
        MPI_DOUBLE,
        0,
        comm);

    if (vector)
    {
        free(vector);
    }
}

/**
 * Prints a matrix to the stndard output stream.
 *
 * @param title       the user-friendly name of the matrix.
 * @param localMatrix the local matrix.
 * @param m           the number of rows in the matrix.
 * @param localM      the local number of rows in the matrix.
 * @param n           the number of columns in the matrix.
 * @param rank        the communicator identifier.
 * @param comm        the communicator.
 */
static void mpimatrix_print_matrix(
    String title,
    DoubleMatrix localMatrix,
    int m,
    int localM,
    int n,
    int rank,
    MPI_Comm comm)
{
    DoubleMatrix matrix;

    if (rank == 0)
    {
        matrix = double_matrix(m, n);

        mpimatrix_assert(
            matrix,
            "mpimatrix_print_matrix",
            "Can't allocate temporary matrix",
            comm);
    }
    else
    {
        matrix = NULL;
    }

    MPI_Gather(
        localMatrix,
        localM * n,
        MPI_DOUBLE,
        matrix,
        localM * n,
        MPI_DOUBLE,
        0,
        comm);

    if (matrix)
    {
        printf("\nThe matrix %s\n", title);

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%f ", matrix[i * n + j]);
            }

            printf("\n");
        }

        printf("\n");
        free(matrix);
    }
}

/**
 * Prints a vector to the standard output stream.
 * 
 * @param title       the user-friendly name of the vector.
 * @param localVector the local vector.
 * @param n           the length of the vector.
 * @param localN      the local length of the vector.
 * @param rank        the communicator identifier.
 * @param comm        the communicator.
 */
static void mpimatrix_print_vector(
    String title,
    DoubleArray localVector,
    int n,
    int localN,
    int rank,
    MPI_Comm comm)
{
    DoubleArray vector;

    if (rank == 0)
    {
        vector = double_array(n);

        mpimatrix_assert(
            vector,
            "mpimatrix_print_vector",
            "Can't allocate temporary vector",
            comm);
    }

    MPI_Gather(
        localVector,
        localN,
        MPI_DOUBLE,
        vector,
        localN,
        MPI_DOUBLE,
        0,
        comm);

    if (vector)
    {
        printf("\nThe vector %s\n", title);

        for (int i = 0; i < n; i++)
        {
            printf("%f ", vector[i]);
        }

        printf("\n");
        free(vector);
    }
}

/**
 * Multiplies a matrix by a vector.
 *  
 * @param localA the local matrix factor.
 * @param localX the local vector factor.
 * @param localM the local number of rows in the matrix.
 * @param n      the number of columns in the matrix.
 * @param localN the local number of columns in the matrix.
 * @param comm   the communicator.
 * @return The local product of the local matrix and vector factors.
 */
static DoubleArray mpimatrix_multiply(
    DoubleMatrix localA,
    DoubleArray localX,
    int localM,
    int n,
    int localN,
    MPI_Comm comm)
{
    DoubleArray localY = double_array(localM);
    DoubleArray x = double_array(n);

    mpimatrix_assert(
        x,
        "mpimatrix_multiply",
        "Can't allocate temporary vector",
        comm);
    MPI_Allgather(localX, localN, MPI_DOUBLE, x, localN, MPI_DOUBLE, comm);

    for (int localI = 0; localI < localM; localI++)
    {
        localY[localI] = 0;

        for (int j = 0; j < n; j++)
        {
            localY[localI] += localA[localI * n + j] * x[j];
        }
    }

    free(x);

    return localY;
}

/**
 * The main entry point for the application.
 *
 * @param count     the number of command-line arguments.
 * @param arguments a collection of command-line arguments. The length of the
 *                  collection is given by the `count` parameter.
 * @return An exit code. This value is always 0, indicating success. However,
 *         the process may exit with an error code of 1, indicating failure
 *         outside the main entry point.
 */
int main(int count, StringArray arguments)
{
    int m;
    int n;
    int rank;
    int size;

    MPI_Init(&count, &arguments);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    mpimatrix_read(rank, size, MPI_COMM_WORLD, &m, &n);

    int localM = m / size;
    int localN = n / size;
    DoubleMatrix localA = double_matrix(localM, n);
    DoubleArray localX = double_array(localN);

    mpimatrix_assert(
        localA && localX && localY,
        "main",
        "Can't allocate local arrays",
        MPI_COMM_WORLD);
    mpimatrix_read_matrix("A", localA, m, localM, n, rank, MPI_COMM_WORLD);
    mpimatrix_print_matrix("A", localA, m, localM, n, rank, MPI_COMM_WORLD);
    mpimatrix_read_vector("x", localX, n, localN, rank, MPI_COMM_WORLD);
    mpimatrix_print_vector("x", localX, n, localN, rank, MPI_COMM_WORLD);
    
    DoubleMatrix localY = mpimatrix_multiply(
        localA,
        localX,
        localM,
        n,
        localN,
        MPI_COMM_WORLD);

    mpimatrix_print_vector("y", localY, m, localM, rank, MPI_COMM_WORLD);
    free(localA);
    free(localX);
    free(localY);
    MPI_Finalize();

    return 0;
}
