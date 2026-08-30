#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
   int item;
   struct node *next;
} NODE;

static NODE *head = NULL;
static NODE *tail = NULL;

void put(const int x)
{
   NODE *new_node = malloc(sizeof *new_node);

   if (new_node == NULL)
   {
      exit(EXIT_FAILURE);
   }

   new_node->item = x;
   new_node->next = NULL;

   if (tail != NULL)
   {
      tail->next = new_node;
   }
   else
   {
      head = new_node;
   }

   tail = new_node;
}

int get()
{
   if (head == NULL)
   {
      exit(EXIT_FAILURE);
   }

   NODE *old = head;
   const int value = old->item;
   head = head->next;

   if (head == NULL)
   {
      tail = NULL;
   }

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
         exit(EXIT_FAILURE);
      }

      put(x);
   }

   printf("czy pusty=%d\n", empty());

   while (!empty())
   {
      printf("+++z FIFO: %d\n", get());
   }

   return 0;
}