#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * The main entry point for the application.
 * 
 * @return An exit code. This value is always 0, indicating success.
 */
int main()
{
    srand(time(NULL));

    int i;
    int frequencies[10] = {0};

    for (i = 0; i < 1000; i++)
    {
        frequencies[(rand() % 10)]++;
    }

    for (i = 0; i < 10; i++)
    {
        printf("Number: %d, Frequency: %d\n", i + 1, frequencies[i]);
    }

    int mode = 0;

    for (i = 1; i < 10; i++)
    {
        if (frequencies[i] > frequencies[mode])
        {
            mode = i;
        }
    }

    printf("Mode: %d\n", mode + 1);

    return 0;
}
