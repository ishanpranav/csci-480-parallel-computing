#include <stdio.h>

extern int __problem1(int n);

static int problem1(int n)
{
    int a = 0;
    
    for (int i = 1; i <= n; i++)
    {
        a += i;
    }
    
    return a;
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
    printf("%d = %d\n", problem1(n), __problem1(n));

    return 0;
}
