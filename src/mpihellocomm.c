#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include "core.h"

const int MAX_STRING = 100;

/**
 * The main entry point for the application.
 *
 * @param count     the number of command-line arguments.
 * @param arguments a collection of command-line arguments. The length of the
 *                  collection is given by the `count` parameter.
 * @return An exit code. This value is always 0, indicating success.
 */
int main(int count, StringArray arguments)
{
    int size;
    int rank;
    char greeting[MAX_STRING];

    MPI_Init(&count, &arguments);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        printf("Greetings from process %d of %d!\n", rank, size);

        for (int comm = 1; comm < size; comm++)
        {
            MPI_Recv(
                greeting,
                MAX_STRING,
                MPI_CHAR,
                comm,
                0,
                MPI_COMM_WORLD,
                MPI_STATUS_IGNORE);

            printf("%s\n", greeting);
        }
    }
    else
    {
        sprintf(
            greeting,
            "Greetings from process %d of %d!",
            rank,
            size);
        MPI_Send(
            greeting,
            strlen(greeting) + 1,
            MPI_CHAR,
            0,
            0,
            MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
