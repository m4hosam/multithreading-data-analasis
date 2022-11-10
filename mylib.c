#include <stdio.h>
#include "mylib.h"

void test_empty(void)
{
    int count = 0;
    for (int i = 0; i < 1000000000; i++)
    {
        count++;
    }
    puts("Hello from C");
}

int test(int from, int to)
{
    int i;
    int s = 0;

    for (i = from; i < to; i++)
        if (i % 3 == 0)
            s += i;

    return s;
}

float test_add(float x, float y)
{
    return x + y;
}

void test_passing_array(int *data, int len)
{
    printf("Data as received from Python\n");
    for (int i = 0; i < len; ++i)
    {
        printf("%d ", data[i]);
    }
    puts("");

    // Modifying the array
    for (int i = 0; i < len; ++i)
    {
        data[i] = -i;
    }
}