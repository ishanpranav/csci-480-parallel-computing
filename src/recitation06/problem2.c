#include <stdio.h>

extern int __problem2(int *x, int *y);

static int problem2(int *x, int *y)
{
    int result = *y * 3;
    
    *x = result - 4;
    *y = *x + 3;

    return result;
}

/**
 * The main entry point for the application.
 *
 * @return An exit code. This value is always 0.
 */
int main()
{
    int x1;
    int y1;

    scanf("%d %d", &x1, &y1);

    int x2 = x1;
    int y2 = y1;
    int result1 = problem2(&x1, &y1);
    int result2 = __problem2(&x2, &y2);

    printf("(%d, %d, %d) = (%d, %d, %d)\n", x1, y1, result1, x2, y2, result2);

    return 0;
}
