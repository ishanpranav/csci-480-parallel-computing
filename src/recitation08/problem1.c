#include <stdio.h>

extern int __problem1(long *a, long *b, long *c);

static int problem1(long *a, long *b, long *c)
{
    int result = *a;
    int cx = (*b * 3) * result;

    while (result > cx)
    {
        int two = result * 2;

        cx = result + two;
        result = two;
    }

    return result;
}

/**
 * The main entry point for the application.
 *
 * @return An exit code.
 */
int main()
{
    long a1;
    long b1;
    long c1;

    scanf("%ld %ld %ld", &a1, &b1, &c1);

    long a2 = a1;
    long b2 = b1;
    long c2 = c1;
    int result1 = problem1(&b1, &c1, &a1);
    int result2 = __problem1(&b2, &c2, &a2);
    
    printf(
        "%d = %d\n%ld = %ld\n%ld = %ld\n%ld = %ld\n",
        result1, result2, a1, a2, b1, b2, c1, c2);

    return 0;
}
