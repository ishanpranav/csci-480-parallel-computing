#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define BITS_PER_BYTE 8
#define BIT_VECTOR_CHUNK_SIZE (sizeof(int) * BITS_PER_BYTE)

struct PrimeList;

typedef enum PrimeListType PrimeListType;
typedef struct PrimeList *PrimeList;

PrimeList wide_prime_list(int length);
PrimeList slim_prime_list(int length);

void prime_list_filter(PrimeList instance, int n);
void prime_list_write(PrimeList instance, int n, FILE *stream);
void finalize_prime_list(PrimeList instance);

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

    omp_set_num_threads(threads);

    PrimeList list;
    
    if (threads > 8)
    {
        list = wide_prime_list(n - 1);
    }
    else
    {
        list = slim_prime_list(n - 1);
    }

    if (!list)
    {
        printf("Error: Out of memory.\n");

        return 1;
    }

    double start = omp_get_wtime();

    prime_list_filter(list, n);

    double elapsed = omp_get_wtime() - start;

    printf("time: %lf\n", elapsed);

    char buffer[13];

    sprintf(buffer, "%ld.txt", n);

    FILE *stream = fopen(buffer, "w");

    if (!stream)
    {
        printf("Error: I/O.\n");

        return 1;
    }

    prime_list_write(list, n, stream);
    fclose(stream);
    finalize_prime_list(list);

    return 0;
}

struct PrimeList
{
    union
    {
        bool *wideImpl;
        int *slimImpl;
    };
    bool slim;
};

PrimeList wide_prime_list(int length)
{
    PrimeList instance = malloc(sizeof *instance);

    if (!instance)
    {
        return NULL;
    }

    bool *wideImpl = calloc(length, sizeof *wideImpl);

    if (!wideImpl)
    {
        free(instance);

        return NULL;
    }

    instance->slim = false;
    instance->wideImpl = wideImpl;

    return instance;
}

PrimeList slim_prime_list(int length)
{
    if (length <= 0)
    {
        return NULL;
    }

    PrimeList instance = malloc(sizeof *instance);

    if (!instance)
    {
        return NULL;
    }

    int *slimImpl = calloc(
        length / BIT_VECTOR_CHUNK_SIZE + (length % BIT_VECTOR_CHUNK_SIZE != 0),
        sizeof *slimImpl);

    if (!slimImpl)
    {
        free(instance);

        return NULL;
    }

    instance->slim = true;
    instance->slimImpl = slimImpl;

    return instance;
}

void wide_prime_list_filter(bool *wideImpl, int n)
{
    long end = (n - 1) / 2;

    for (long i = 0; i <= end; i++)
    {
        if (wideImpl[i])
        {
            continue;
        }

#pragma omp parallel for
        for (long j = i + 1; j <= n - 2; j++)
        {
            if (wideImpl[j])
            {
                continue;
            }

            if ((j + 2) % (i + 2) == 0)
            {
                wideImpl[j] = 1;
            }
        }
    }
}

void slim_prime_list_filter(int *slimImpl, int n)
{
    long end = (n - 1) / 2;

    for (long i = 0; i <= end; i++)
    {
        if (slimImpl[i / BIT_VECTOR_CHUNK_SIZE] &
            (1 << (i % BIT_VECTOR_CHUNK_SIZE)))
        {
            continue;
        }

#pragma omp parallel for
        for (long j = i + 1; j <= n - 2; j++)
        {
            int quotient = j / BIT_VECTOR_CHUNK_SIZE;
            int remainder = j % BIT_VECTOR_CHUNK_SIZE;

            if (slimImpl[quotient] & (1 << remainder))
            {
                continue;
            }

            if ((j + 2) % (i + 2) == 0)
            {
                slimImpl[quotient] |= 1 << remainder;
            }
        }
    }
}

void prime_list_filter(PrimeList instance, int n)
{
    if (instance->slim)
    {
        slim_prime_list_filter(instance->slimImpl, n);

        return;
    }

    wide_prime_list_filter(instance->wideImpl, n);
}

void prime_list_write(PrimeList instance, int n, FILE *stream)
{
    long x = 0;

    for (long i = 0; i <= n - 2; i++)
    {
        if (!instance->slim && instance->wideImpl[i])
        {
            continue;
        }

        if (instance->slimImpl[i / BIT_VECTOR_CHUNK_SIZE] &
            (1 << (i % BIT_VECTOR_CHUNK_SIZE)))
        {
            continue;
        }

        x++;

        fprintf(stream, "%ld ", i + 2);
    }

    printf("count: %ld\n", x);
}

void finalize_prime_list(PrimeList instance)
{
    if (instance->slim)
    {
        free(instance->slimImpl);
    }
    else
    {
        free(instance->wideImpl);
    }

    free(instance);
}
