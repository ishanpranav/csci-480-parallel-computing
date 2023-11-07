// mpireduce.c
// Author: Wes Kendall
// Copyright 2013 www.mpitutorial.com
// This code is provided freely with the tutorials on mpitutorial.com. Feel
// free to modify it for your own use. Any distribution of the code must
// either provide a link to www.mpitutorial.com or keep this header in tact.

// Modified and adapted by Ishan Pranav.

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "core.h"
#include "single_array.h"

/**
 * Generates a collection of random single-precision floating-point numbers
 * between 0 and 1.
 * 
 * @param count the number of elements.
 * @return A collection of random single-precision floating-point numbers. The
 *         length of the collection is given by the `count` parameter.
*/
static SingleArray mpireduce_randomize(int count)
{
    SingleArray result = single_array(count);

    for (int i = 0; i < count; i++)
    {
        result[i] = rand() / (float)RAND_MAX;
    }

    return result;
}

/**
 * The main entry point for the application.
 *
 * @param count     the number of command-line arguments.
 * @param arguments a collection of command-line arguments. The length of the
 *                  collection is given by the `count` parameter.
 * @return 1 if fewer than 2 command-line arguments are provided; otherwise, 0.
 */
int main(int count, String arguments[])
{
    if (count != 2)
    {
        fprintf(stderr, "Usage: mpiexec ./mpireduce <elements_per_process>\n");
        
        return 1;
    }

    int elementsPerProcess = atoi(arguments[1]);
    int rank;
    int size;
    
    srand(time(NULL));
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    srand(rank);

    SingleArray array = mpireduce_randomize(elementsPerProcess);
    float localSum = 0;
    float globalSum;

    for (int i = 0; i < elementsPerProcess; i++)
    {
        localSum += array[i];
    }

    printf(
        "Local sum for process %d - %f, average = %f\n",
        rank, 
        localSum, 
        localSum / elementsPerProcess);

    MPI_Reduce(
        &localSum,
        &globalSum, 
        1, 
        MPI_FLOAT, 
        MPI_SUM, 
        0, 
        MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf(
            "Total sum = %f, average = %f\n",
            globalSum,
            globalSum / (size * elementsPerProcess));
    }

    free(array);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return 0;
}
