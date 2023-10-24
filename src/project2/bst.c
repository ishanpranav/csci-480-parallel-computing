// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav. All rights reserved.
// Licensed under the MIT License.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

void add(bst_node **root, char *word)
{
    // Base case: Guard against missing root reference or empty root

    if (!root || !(*root))
    {
        *root = malloc(sizeof *root);
        (*root)->data = word;
        (*root)->left = NULL;
        (*root)->right = NULL;

        return;
    }

    int comparison = strcmp(word, (*root)->data);

    // Recursive case: Binary search

    if (comparison < 0)
    {
        add(&((*root)->left), word);
    }
    else if (comparison > 0)
    {
        add(&((*root)->right), word);
    }

    // Base case: Do not add existing elements
}

void inorder(bst_node *root)
{
    // Base case: Guard against empty root

    if (!root)
    {
        return;
    }

    // Recursive case
    // Up recursion: Move left
    // Down recursion: Move right

    inorder(root->left);
    printf("%s ", root->data);
    inorder(root->right);
}

/**
 * Removes the specified word from the binary search tree. This function is
 * meant for internal (recursive) use only.
 *
 * @param root a pointer to the root node of the tree
 * @param word a pointer to the first character of the zero-terminated string
 *             containing the key to remove from the tree
 * @return A pointer to to the replacement node.
 */
static bst_node *removeWord(bst_node *root, char *word)
{
    int comparison = strcmp(word, root->data);

    if (comparison == 0)
    {
        // Base case: Remove an element without children

        if (!root->left && !root->right)
        {
            free(root);

            return NULL;
        }

        // Base case: Remove an element with a right child only

        if (!root->left)
        {
            bst_node *result = root->right;

            free(root);

            return result;
        }

        // Base case: Remove an element with a left child only

        if (!root->right)
        {
            bst_node *result = root->left;

            free(root);

            return result;
        }
        
        // If the current node has two children, start with the right sub-tree
        // and move to the extreme left to replace the current value with its
        // in-order successor

        bst_node *current = root->right;

        while (current->left)
        {
            current = current->left;
        }

        root->data = current->data;
        root->right = removeWord(root->right, current->data);

        return root;
    }

    // Recursive case: Binary search

    if (comparison < 0)
    {
        root->left = removeWord(root->left, word);
    }
    else
    {
        root->right = removeWord(root->right, word);
    }

    // Base case: Move up the recursive stack

    return root;
}

char *removeSmallest(bst_node **root)
{
    // Guard against missing root reference or empty root

    if (!root || !(*root))
    {
        return NULL;
    }

    // Move to the extreme left

    bst_node *current = *root;

    while (current->left)
    {
        current = current->left;
    }

    // Remove the minimum element

    char *word = current->data;

    *root = removeWord(*root, word);

    return word;
}

char *removeLargest(bst_node **root)
{
    // Guard against missing root reference or empty root

    if (!root || !(*root))
    {
        return NULL;
    }

    // Move to the extreme right

    bst_node *current = *root;

    while (current->right)
    {
        current = current->right;
    }

    // Remove the maximum element
    
    char *word = current->data;

    *root = removeWord(*root, word);

    return word;
}
