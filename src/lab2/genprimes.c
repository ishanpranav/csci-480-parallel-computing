#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int DENOMINATOR = sizeof(int) * 8;

typedef int *BitVector;
//typedef bool *BitVector;

BitVector bit_vector(int length)
{
    if (length <= 0)
    {
        return NULL;
    }

    //return calloc(length, sizeof(bool));
    return calloc(length / DENOMINATOR + (length % DENOMINATOR != 0), sizeof(int));
}

void bit_vector_set(BitVector instance, int index)
{
    instance[index / DENOMINATOR] |= (1 << (index % DENOMINATOR));
    //instance[index] = true;
}

bool bit_vector_get(BitVector instance, int index)
{
    return instance[index / DENOMINATOR] & (1 << (index % DENOMINATOR));
    //return instance[index];
}

/**
 * The main entry point for the application.
 *
 * @param count the number of command-line arguments.
 * @param args  a collection of command-line arguments. The length of the
 *              collection is given by the `count` parameter.
 * @return An exit code. This value is 0, indicating success, or 1, indicating
 *         a usage error.
 */
int main(int count, char *args[])
{
    if (count != 3)
    {
        printf("Usage: genprimes <n> <threads>\n");

        return 1;
    }

    // Since `n` can be up to 10,000,000 we need at least 32 bits (`long`).

    long n = strtol(args[1], NULL, 10);

    if (n < 2 || n > 10000000)
    {
        printf("<n> must be a positive number between 2 and 10,000,000.\n");

        return 1;
    }

    int threads = atoi(args[2]);

    if (threads < 0)
    {
        printf("<threads> must be a positive number.\n");

        return 1;
    }

    // There are (n - 2 + 1) = (n - 1) numbers between 2 (inclusive) and n
    // (inclusive).maps positions to number

    //BitVector filtered = bit_vector(n - 1);
    // int vector[312500];
    BitVector filtered = bit_vector(n - 1);

    if (!filtered)
    {
        printf("Error: Out of memory.\rn");

        return 1;
    }
    
    // We will stop at ((n - 2 + 1) / 2) = ((n - 1) / 2).

    double start = omp_get_wtime();
    long end = (n - 1) / 2;

    for (long i = 0; i <= end; i++)
    {
        if (bit_vector_get(filtered, i))
        {
            continue;
        }

#pragma omp parallel for num_threads(threads)
        for (long j = i + 1; j <= n - 2; j++)
        {
            // does this check help?
            if (bit_vector_get(filtered, j))
            {
                continue;
            }

            if ((j + 2) % (i + 2) == 0)
            {
                bit_vector_set(filtered, j);
            }
        }
    }

    double elapsed = omp_get_wtime() - start;

    printf("time: %lf\n", elapsed);

    // We only need 13 characters in the buffer since the longest valid file
    // name is "10000000.txt" (12 characters terminated by '\0').

    char buffer[13];

    sprintf(buffer, "%ld.txt", n);

    FILE *stream = fopen(buffer, "w");

    if (!stream)
    {
        printf("Error: I/O.\n");
        
        return 1;
    }

    long x = 0;

    for (long i = 0; i <= n - 2; i++)
    {
        if (!bit_vector_get(filtered, i))
        {
            x++;

            fprintf(stream, "%ld ", i + 2);
        }
    }

    fclose(stream);
    free(filtered);
    printf("%ld\n", x);

    return 0;
}
