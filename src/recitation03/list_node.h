/**
 * Represents a linked-list node.
 */
struct ListNode
{
    /**
     * Specifies the node value, a pointer to a zero-terminated string.
     */
    char *word;

    /**
     * Specifies the next node in the linked list. This value is 0 if the node
     * is the tail of the linked list.
     */
    struct ListNode *next;
};

/**
 * Adds a node to the front of a linked list.
 *
 * @param node a pointer to a node
 * @param head a pointer to the head of a linked list (itself a pointer to a
 *             node)
 */
void list_node_push(struct ListNode *node, struct ListNode **head);

/**
 * Reverses the elements of the linked list.
 *
 * @param head a pointer to the head of a linked list (itself a pointer to a
 *             node)
 */
void list_node_reverse(struct ListNode **head);

/**
 * Prints a textual representation of a linked list to the standard output
 * stream.
 *
 * @param current a pointer to the node from which to begin printing the list
 */
void list_node_print(struct ListNode *current);

/**
 * Swaps the middle two elements of a linked list.
 *
 * @param head a pointer to the head of a linked list (itself a pointer to a
 *             node)
 */
void list_node_swap_medians(struct ListNode **head);

/**
 * Moves the first node of a linked list to the end, making it the last node.
 *
 * @param head a pointer to the head of a linked list (itself a pointer to a
 *             node)
 */
void list_node_shift(struct ListNode **head);
