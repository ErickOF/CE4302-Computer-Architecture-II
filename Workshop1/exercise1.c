#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define MAX_ARRAY_SIZE 10000
// 10 000us = 10ms
#define THREAD1_TIME 10000
// 5 000us = 5ms
#define THREAD2_TIME 5000


/**
 * Struct to represent the Pthread arguments
 */
struct PthreadArgs
{
    int *array;
    int delay;
};


/**
 * This function generates a 8-bit random number and store it in an
 * array every 10 ms.
 */
void generate_random_numbers(void* args)
{
    // Get args
    struct PthreadArgs pthread_args = *(struct PthreadArgs*) args;
    int* array = pthread_args.array;
    int delay = pthread_args.delay;

    // Set seed to the random number generator
    srand(time(NULL));

    int i = 0;

    while (i < MAX_ARRAY_SIZE)
    {
        // Generating a 8-bit random number
        array[i] = rand() % 255;
        i++;

        // Sleeping 10ms
        usleep(delay);

        printf("Num %d: %d\n", i - 1, array[i - 1]);
    }
}


int main(int argc, char const *argv[])
{
    // Create the arrays
    int *array1 = malloc(MAX_ARRAY_SIZE * sizeof(int));
    int *array2 = malloc(MAX_ARRAY_SIZE * sizeof(int));

    // Pthreads
    pthread_t thread_id1, thread_id2, thread_id3;
    // Function arguments
    struct PthreadArgs args1 = {array1, THREAD1_TIME};
    struct PthreadArgs args2 = {array2, THREAD2_TIME};

    // Creates threads to generate random numbers
    pthread_create(&thread_id1, NULL, (void*) generate_random_numbers,
                   (void*) &args1);
    pthread_create(&thread_id2, NULL, (void*) generate_random_numbers,
                   (void*) &args2);

    // Starting threads
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    // Free memory
    free(array1);
    free(array2);

    return 0;
}
