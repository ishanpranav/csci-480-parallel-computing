#include <stdio.h>

extern long __problem2(int n);

static long problem2(int n)
{
    if (n <= 1)
    {
        return 1;
    }

    long result = 1;
    
    for (int i = 1; i <= n; i++)
    {
        result *= i;
    }
    
    return result;
}

/**
 * The main entry point for the application.
 *
 * @return An exit code. This value is always 0.
 */
int main()
{
    int n;

    scanf("%d", &n);
    printf("%ld %ld\n", problem2(n), __problem2(n));

    return 0;
}
