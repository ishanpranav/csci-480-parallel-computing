#include "core.h"
#include "double_array.h"
#include <mpi.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void mpimatrix_assert(
    bool localOk,
    String firstName,
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
            fprintf(stderr, "Proc %d > In %s, %s\n", rank, firstName, message);
            fflush(stderr);
        }

        MPI_Finalize();
        exit(1);
    }
}

static void mpimatrix_read(
    int *m,
    int *localM,
    int *n,
    int *localN,
    int rank,
    int size,
    MPI_Comm comm)
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

    *localM = *m / size;
    *localN = *n / size;
}

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

static void mpimatrix_multiply(
    String title,
    DoubleMatrix localA,
    DoubleArray localX,
    DoubleArray localY,
    int localM,
    int n,
    int localN,
    MPI_Comm comm)
{
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
    DoubleMatrix localA;
    DoubleArray localX;
    DoubleArray localY;
    int m;
    int n;
    int localM;
    int localN;
    int rank;
    int size;

    MPI_Init(&count, &arguments);

    MPI_Comm comm = MPI_COMM_WORLD;

    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);
    mpimatrix_read(&m, &localM, &n, &localN, rank, size, comm);

    localA = double_matrix(localM, n);
    localX = double_array(localN);
    localY = double_array(localM);

    mpimatrix_assert(
        localA && localX && localY,
        "main",
        "Can't allocate local arrays",
        comm);
    mpimatrix_read_matrix("A", localA, m, localM, n, rank, comm);
    mpimatrix_print_matrix("A", localA, m, localM, n, rank, comm);
    mpimatrix_read_vector("x", localX, n, localN, rank, comm);
    mpimatrix_print_vector("x", localX, n, localN, rank, comm);
    mpimatrix_multiply(localA, localX, localY, localM, n, localN, comm);
    mpimatrix_print_vector("y", localY, m, localM, rank, comm);
    free(localA);
    free(localX);
    free(localY);
    MPI_Finalize();

    return 0;
}
