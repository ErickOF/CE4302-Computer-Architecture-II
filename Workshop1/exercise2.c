#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


long long int counter = 0;
pthread_mutex_t lock;


/**
 * This function add one to a global variable.
 * 
 *      - void* args - pthread id.
 */
void add(void* args)
{
    pthread_t id = *(pthread_t*) args;

    while (counter < 100)
    {
        printf("Thread %ld starts\n", id);

        // Lock mutex
        pthread_mutex_lock(&lock);

        printf("Mutex was locked\n");
        counter++;

        // Unlock mutex
        pthread_mutex_unlock(&lock);
        printf("Mutex was unlocked and thread %ld ends\n", id);

        sleep(1);
    }
}


int main(int argc, char const *argv[])
{
    // PThreads
    pthread_t thread_id1, thread_id2;

    pthread_mutex_init(&lock, NULL);

    // Threads to add one to a global variable
    pthread_create(&thread_id1, NULL, (void*) add, (void*) &thread_id1);
    pthread_create(&thread_id2, NULL, (void*) add, (void*) &thread_id2);

    // Starting threads
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}
