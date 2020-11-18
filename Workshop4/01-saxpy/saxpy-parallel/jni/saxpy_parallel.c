#include <arm_neon.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * This functions creates a vector with random numbers.
 * 
 * const int N - size of the vector.
 * int32_t* v    - pointer with memory allocated.
 */
void create_random_vector(const int N, int32_t* v)
{
    for (int i = 0; i < N; i++)
    {
        // Get a random number
        v[i] = rand();
    }
}

/**
 * This functions computes the saxpy operation.
 * Single-Precision A·X Plus Y.
 * 
 * const int N     - size of the vectors.
 * const int A     - constant of the operation.
 * int32_t* x      - first vector.
 * int32_t* y      - second vector.
 * int32_t* result - saxpy operation result.
 */
void saxpy(const int N, const int A, int32_t* x, int32_t* y, int32_t* result)
{
    int i;
    int values[N];

    // Set share and private values in parallel region
    #pragma simd
    for (i = 0; i < N; i += 4)
    {
        // Duplicate vector element to vector or scalar
        int32x4_t An = vmovq_n_s32(A);

        // Compute each value
        int32x4_t xn = vld1q_s32(x + i);
        int32x4_t yn = vld1q_s32(y + i);
        int32x4_t result_n = vaddq_s32(vmulq_s32(An, xn), yn);

        vst1q_s32(result + i, result_n);
    }
}

int main(int argc, char const *argv[])
{
    // Times
    double start_time, run_time;

    // Init random library
    srand(0);

    for (int i = 1; i <= 3; i++)
    {
        // Number of elements
        const long int N = i * 10000000;
        
        // Vectors
        int32_t* x = (int32_t*) calloc(N, sizeof(int32_t));
        int32_t* b = (int32_t*) calloc(N, sizeof(int32_t));
        int32_t* y = (int32_t*) calloc(N, sizeof(int32_t));
    
        // Constant
        const int A = 123;
        
        // Init vectors;
        create_random_vector(N, x);
        create_random_vector(N, b);

        // Use two threads
        omp_set_num_threads(8);

        // Run saxpy
        start_time = omp_get_wtime();

        saxpy(N, A, x, b, y);

        run_time = omp_get_wtime() - start_time;

        printf("\n saxpy with %ld value in %lf seconds\n ", N, run_time);

        // Free memory
        free(x);
        free(b);
        free(y);
    }
}
