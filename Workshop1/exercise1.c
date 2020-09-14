#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define MAX_ARRAY_SIZE 32
// 10 000us = 10ms
#define THREAD1_TIME 10000
// 5 000us = 5ms
#define THREAD2_TIME 5000


/**
 * Struct to represent the Pthread arguments of the random number generator
 * function.
 */
struct PthreadArgsRNG
{
    int *array;
    int delay;
};

/**
 * Struct to represent the Pthread arguments of the XOR function.
 */
struct PthreadArgsXOR
{
    int *array1;
    int *array2;
};


/**
 * This function generates a 8-bit random number and store it in an
 * array every 10 ms.
 * 
 * Params:
 *      - PthreadArgsRNG struct pointer as a void pointer.
 */
void generate_random_numbers(void* args)
{
    // Get args
    struct PthreadArgsRNG pthread_args = *(struct PthreadArgsRNG*) args;
    int* array = pthread_args.array;
    int delay = pthread_args.delay;

    // Set seed to the random number generator
    srand(time(NULL));

    int i = 0;

    while (1)
    {
        // Generating a 8-bit random number
        array[i] = rand() % 256;
        // Restart if i is equal to MAX_ARRAY_SIZE otherwise go to the next 
        i = i == MAX_ARRAY_SIZE ? 0 : i + 1;

        // Sleeping 10ms
        usleep(delay);
    }
}

/**
 *
 */
void do_xor(void* args)
{
    // Get args
    struct PthreadArgsXOR pthread_ags = *(struct PthreadArgsXOR*) args;
    int* array1 = pthread_ags.array1;
    int* array2 = pthread_ags.array2;

    int i = 0;

    while (1)
    {
        const int xor = array1[i] ^ array2[i];
        // Restart if i is equal to MAX_ARRAY_SIZE otherwise go to the next 
        i = i == MAX_ARRAY_SIZE ? 0 : i + 1;

        // Display char
        printf("%c\n", xor);
    }
    
}


int main(int argc, char const *argv[])
{
    // Create the arrays
    int *array1 = malloc(MAX_ARRAY_SIZE * sizeof(int));
    int *array2 = malloc(MAX_ARRAY_SIZE * sizeof(int));

    // Pthreads
    pthread_t thread_id1, thread_id2, thread_id3;

    // Functions arguments
    struct PthreadArgsRNG args1 = {array1, THREAD1_TIME};
    struct PthreadArgsRNG args2 = {array2, THREAD2_TIME};
    struct PthreadArgsXOR args3 = {array1, array2};

    // Threads to generate random numbers in different times
    pthread_create(&thread_id1, NULL, (void*) generate_random_numbers,
                   (void*) &args1);
    pthread_create(&thread_id2, NULL, (void*) generate_random_numbers,
                   (void*) &args2);
    // Thread to display every char resulting of the XOR of the two arrays
    pthread_create(&thread_id3, NULL, (void*) do_xor,
                   (void*) &args3);

    // Starting threads
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    pthread_join(thread_id3, NULL);

    // Free memory
    free(array1);
    free(array2);

    return 0;
}
