#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

struct Args
{
    int start;
    int end;
} typedef Args;

void *testThread(void *arguments)
{
    clock_t time_start = clock();
    struct Args *args = (struct Args *)arguments;
    sleep(3);
    printf("start: %d end: %d\n", args->start, args->end);
    clock_t time_end = clock();
    double cpu_time_used = ((double)(time_end - time_start)) / CLOCKS_PER_SEC;
    printf("%f\n", cpu_time_used);
}

void *threadedSort(int NUM_THREADS)
{
    int start, end;

    int num = 1000000 / NUM_THREADS;

    pthread_t threads[NUM_THREADS];
    struct Args *args = malloc(sizeof(struct Args) * NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        args[i].start = i * num + 1;
        args[i].end = (i + 1) * num;
        // printf("start: %d, end: %d\n", args[i].start, args[i].end);
        pthread_create(&threads[i], NULL, testThread, &args[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
}

int main()
{
    threadedSort(8);
    return 0;
}
