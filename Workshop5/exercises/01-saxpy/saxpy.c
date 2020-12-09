#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/**
 * This functions creates a vector with random numbers.
 * 
 * const int N - size of the vector.
 * float* v    - pointer with memory allocated.
 */
void create_random_vector(const int N, float* v)
{
    for (int i = 0; i < N; i++)
    {
        // Get a random number
        v[i] = (float) rand();
    }
}

/**
 * This functions computes the saxpy operation.
 * Single-Precision A·X Plus Y.
 * 
 * const int N   - size of the vectors.
 * const float A - constant of the operation.
 * float* x      - first vector.
 * float* y      - second vector.
 * float* result - saxpy operation result.
 */
void saxpy(const int N, const float A, float* x, float* y, float* result)
{
    for (int i = 0; i < N; i++)
    {
        // Compute each result
        result[i] = A*x[i] + y[i];
    }
}


int main(int argc, char const *argv[])
{
    // Times
    clock_t start_time, run_time;

    // Init random library
    srand(0);

    for (int i = 4; i < 7; i++)
    {
        // Number of elements
        const long int N = pow(2, i)*1024;
        
        // Vectors
        float* x = (float*) malloc(N*sizeof(float));
        float* b = (float*) malloc(N*sizeof(float));
        float* y = (float*) malloc(N*sizeof(float));

        // Constant
        const float A = 123;

        // Init vectors;
        create_random_vector(N, x);
        create_random_vector(N, b);

        // Run saxpy
        start_time = clock();
        saxpy(N, A, x, b, y);
        run_time = clock() - start_time;
        printf("Saxpy in CPU with %ld value in %lf seconds\n\n", N,
               (double) run_time / CLOCKS_PER_SEC);

        // Free memory
        free(x);
        free(b);
        free(y);
    }
}
