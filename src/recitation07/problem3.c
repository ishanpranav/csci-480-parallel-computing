#include <stdio.h>

extern int __problem3Part1(int n);
extern int __problem3Part2(int n);

static int problem3Part1(int n)
{
    int result = 0;

    for (int i = 0; i <= n; i += 2)
    {
        result += i;
    }

    return result;
}

static int problem3Part2(int n)
{
    int result = 0;

    for (int i = 1; i <= n; i += 2)
    {
        result += i;
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
    int n1;
    int n2;

    scanf("%d %d", &n1, &n2);
    printf("(%d, %d) = (%d, %d)\n", 
        problem3Part1(n1),
        problem3Part2(n2),
        __problem3Part1(n1),
        __problem3Part2(n2));
}
