#include "stdio.h"
#include "list_node.h"

void list_node_push(struct ListNode *node, struct ListNode **head)
{
    node->next = *head;
    *head = node;
}

void list_node_reverse(struct ListNode **head)
{
    if (head == NULL)
    {
        return;
    }

    struct ListNode *current = *head;

    if (current == NULL)
    {
        return;
    }

    struct ListNode *previous = NULL;

    // *[A] -> [B] -> [C] -> [D] -> [E]

    // 1. *[A]
    //     [B] -> [C] -> [D] -> [E]

    // 2. [B] -> *[A]
    //    [C]  -> [D] -> [E]

    // 3. [C] -> [B] -> *[A]
    //    [D] -> [E]

    // 4. [D] -> [C] -> [B] -> *[A]
    ///   [E]

    // 5. [E] -> [D] -> [C] -> [B] -> *[A]

    while (current != NULL)
    {
        struct ListNode *next = current->next;

        current->next = previous;
        previous = current;
        current = next;
    }

    // *[E] -> [D] -> [C] -> [B] -> [A]

    *head = previous;
}

void list_node_print(struct ListNode *current)
{
    while (current != NULL)
    {
        printf("%s ", current->word);

        current = current->next;
    }

    printf("\n");
}

void list_node_swap_medians(struct ListNode **head)
{
    // Floyd's cycle-finding algorithm: technique to find the middle
    // The 'slow' pointer iterates over every node; the 'fast' pointer
    // iterates over every other node. When the 'fast' pointer reaches
    // the end, the 'slow'  pointer must have reached the middle.

    struct ListNode *slow = *head;
    struct ListNode *fast = *head;
    struct ListNode *previous = NULL;

    for (;;)
    {
        fast = fast->next->next;

        if (fast == NULL || fast->next == NULL)
        {
            break;
        }

        previous = slow;
        slow = slow->next;
    }

    // There is an odd number of nodes

    if (fast != NULL)
    {
        return;
    }

    struct ListNode *current = previous->next;
    struct ListNode *next = current->next;

    // Swap the nodes

    previous->next = next;
    current->next = next->next;
    next->next = current;
}

void list_node_shift(struct ListNode **head)
{
    struct ListNode *current = *head;

    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = *head;
    *head = (*head)->next;
    current->next->next = NULL;
}
