#include <stdio.h>
#define N 100

static int stack[N];
static int head = 0;

void push(const int x)
{
   if (head == N)
   {
      return;
   }

   stack[head] = x;
   head++;
}

int pop()
{
   if (head == 0)
   {
      return -1;
   }

   head--;
   return stack[head];
}

int size()
{
   return head;
}

int full()
{
   if (head == N)
   {
      return 1;
   }

   return 0;
}

int main()
{
   int i;
   int x;

   for (i = 0; i < 10; i++)
   {
      if (scanf("%d", &x) != 1)
      {
         return 1;
      }

      push(x);
   }

   for (i = 0; i < head; i++)
   {
      printf("-- %d\n", stack[i]);
   }

   printf("--- head=%d\n", head);
   printf("rozmiar stosu=%d\n", size());
   printf("czy pelny=%d\n", full());

   const int head1 = head;
   for (i = 0; i < head1; i++)
   {
      printf("+++ze stosu: %d\n", pop());
   }

   printf("head=%d\n", head);

   return 0;
}
