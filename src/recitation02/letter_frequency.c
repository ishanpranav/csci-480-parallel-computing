#include <stdio.h>

/**
 * The main entry point for the application.
 *
 * @return An exit code. This value is always 0, indicating success.
 */
int main()
{
    int frequencies[128] = {0};
    char input[128] = {0};

    printf("Enter up to 127 characters: ");
    scanf("%s", input);

    char *pInput = input;
    char symbol;

    do
    {
        symbol = *pInput;
        frequencies[symbol]++;
        pInput++;
    } while (symbol != '\0');

    int i;
    char mode = '\0';

    for (i = 1; i < 128; i++)
    {
        int frequency = frequencies[i];

        if (frequency > 0)
        {
            printf("'%c' = %d\n", i, frequency);

            if (frequency > frequencies[mode])
            {
                mode = i;
            }
        }
    }

    printf("Most common character: %c\n", mode);

    return 0;
}
