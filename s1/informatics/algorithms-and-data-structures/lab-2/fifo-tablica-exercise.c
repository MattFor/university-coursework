#include <stdio.h>
#define N 100

static int fifo[N];
static int head = 0;
static int tail = 0;
static int l = 0;

void put(const int x)
{
    if (l == N)
    {
        return;
    }

    fifo[tail] = x;
    tail = (tail + 1) % N;
    l++;
}

int get()
{
    if (l == 0)
    {
        return -1;
    }

    const int value = fifo[head];
    head = (head + 1) % N;
    l--;

    return value;
}

int full()
{
    if (l == N)
    {
        return 1;
    }

    return 0;
}

int empty()
{
    if (l == 0)
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

        put(x);
    }

    for (i = head; i != tail; i = (i + 1) % N)
    {
        printf("-- %d\n", fifo[i]);
    }

    printf("dlugosc kolejki=%d\n", l);
    printf("--- head=%d\n--- tail=%d\n", head, tail);
    printf("czy pelny=%d\n", full());
    printf("czy pusty=%d\n", empty());

    for (i = 0; i < 5; i++)
    {
        printf("+++z fifo: %d\n", get());
    }

    printf("dlugosc kolejki=%d\n", l);
    printf("--- head=%d\n--- tail=%d\n", head, tail);

    return 0;
}