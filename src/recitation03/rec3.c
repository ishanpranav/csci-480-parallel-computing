#include <stdio.h>
#include "list_node.h"

/**
 * The main entry point for the application.
 *
 * @return An exit code. This value is 0 if all assertions succeed.
 */
int main()
{
    struct ListNode *head = NULL;
    struct ListNode first = {"1", NULL};
    struct ListNode second = {"2", NULL};
    struct ListNode third = {"3", NULL};
    struct ListNode fourth = {"4", NULL};
    struct ListNode fifth = {"5", NULL};
    struct ListNode sixth = {"6", NULL};

    list_node_push(&first, &head);
    list_node_push(&second, &head);
    list_node_push(&third, &head);
    list_node_push(&fourth, &head);
    list_node_push(&fifth, &head);
    list_node_push(&sixth, &head);
    printf("Values: ");
    list_node_print(head);
    list_node_reverse(&head);
    printf("Reversed: ");
    list_node_print(head);
    list_node_reverse(&head);
    printf("Reversed again (original): ");
    list_node_print(head);
    printf("Swap middle: ");
    list_node_swap_medians(&head);
    list_node_print(head);
    list_node_swap_medians(&head);
    printf("Swap middle again (original): ");
    list_node_print(head);

    return 0;
}
