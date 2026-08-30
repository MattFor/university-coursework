#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int item;
    struct node *next;
} NODE;

static NODE *head = NULL;

void push(const int x)
{
    NODE *new_node = malloc(sizeof *new_node);

    if (new_node == NULL)
    {
        exit(EXIT_FAILURE);
    }

    new_node->item = x;
    new_node->next = head;
    head = new_node;
}

int pop()
{
    if (head == NULL)
    {
        exit(EXIT_FAILURE);
    }

    NODE *old = head;
    const int value = old->item;
    head = head->next;

    free(old);
    return value;
}

int empty()
{
    if (head == NULL)
    {
        return 1;
    }

    return 0;
}

int main()
{
    int x;

    for (int i = 0; i < 10; i++)
    {
        if (scanf("%d", &x) != 1)
        {
            return 1;
        }

        push(x);
    }

    printf("czy pusty=%d\n", empty());

    while (!empty())
    {
        printf("+++ze stosu: %d\n", pop());
    }

    return 0;
}
