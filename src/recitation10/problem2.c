#include <stdio.h>

extern int __problem2(long *xp, long *yp, long *zp);

static int problem2(long *xp, long *yp, long *zp)
{
    long t0 = *xp * 2;
    long t1 = *yp * t0;

    if (t1 + 3 < t0)
    {
        t1 = (t0 - 4) * 15;
    }
    else if (t1 * 5 < 6)
    {
        t0 = 9;
    }
    else
    {
        t1 = 4;
    }

    *xp = t1;
    *yp = t0;

    return (5 - t1) * t0;
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
    int result1 = problem2(&a1, &b1, &c1);
    int result2 = __problem2(&a2, &b2, &c2);

    printf(
        "%d = %d\n%ld = %ld\n%ld = %ld\n%ld = %ld\n",
        result1, result2, a1, a2, b1, b2, c1, c2);

    return 0;
}
