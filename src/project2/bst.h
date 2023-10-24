// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav. All rights reserved.
// Licensed under the MIT License.

#ifndef BST_H_
#define BST_H_

/**
 * Represents a node structure for use with the binary search tree.
 */
typedef struct bst_node
{
    /**
     * Specifies a pointer to the first character of a zero-terminated string
     * value of the node.
     */
    char *data;

    /**
     * Specifies a pointer to the right child node.
     */
    struct bst_node *right;

    /**
     * Specifies a pointer to the left child node.
     */
    struct bst_node *left;
} bst_node;

/**
 * Adds a value to the binary search tree.
 *
 * @param root a pointer to the root node of the tree
 */
void add(bst_node **root, char *word);

/**
 * Prints the values stored in the binary search tree according to the inorder
 * traversal. The values should be separated by a single space.
 *
 * @param root a pointer to the root node of the tree
 */
void inorder(bst_node *root);

/**
 * Removes the node with the smallest value in the tree.
 *
 * @param root a pointer to the root node of the tree
 * @return A pointer to the first character of the zero-terminated string value
 *         of the removed node, or NULL if no node was removed.
 */
char *removeSmallest(bst_node **root);

/**
 * Removes the node with the largest value in the tree.
 *
 * @param root a pointer to the root node of the tree
 * @return A pointer to the first character of the zero-terminated string value
 *         of the removed node, or NULL if no node was removed.
 */
char *removeLargest(bst_node **root);

#endif
