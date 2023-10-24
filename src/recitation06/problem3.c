#include <stdio.h>

extern int __problem3(int *x, int *y);

static int problem3(int *x, int *y)
{
    int result = *y;
    
    result <<= 4;
    
    int dx = *x;
    
    dx *= 5;
    *x = dx;
    dx += 3;
    *y = dx;

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
    int result1 = problem3(&x1, &y1);
    int result2 = __problem3(&x2, &y2);

    printf("(%d, %d, %d) = (%d, %d, %d)\n", x1, y1, result1, x2, y2, result2);

    return 0;
}
