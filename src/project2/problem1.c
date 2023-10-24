#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

int main()
{
    bst_node *root = NULL;
    char *instruction = (char *)malloc(256 * sizeof(char));
    char *word = NULL;

    while (scanf("%s", instruction) > 0)
    {
        if (strncmp(instruction, "a", 2) == 0)
        {
            word = (char *)malloc(256 * sizeof(char));

            scanf("%s\n", word);
            add(&root, word);
        }
        else if (strncmp(instruction, "s", 2) == 0)
        {
            word = removeSmallest(&root);

            if (word)
            {
                free(word);

                word = NULL;
            }
        }
        else if (strncmp(instruction, "l", 2) == 0)
        {
            word = removeLargest(&root);

            if (word)
            {
                free(word);

                word = NULL;
            }
        }
        else if (strncmp(instruction, "p", 2) == 0)
        {
            inorder(root);
            printf("\n");
        }
        else
        {
            printf("Error: %s is not a valid instruction\n", instruction);
        }
    }

    if (word)
    {
        free(word);

        word = NULL;
    }

    if (instruction)
    {
        free(instruction);

        instruction = NULL;
    }

    return 0;
}
