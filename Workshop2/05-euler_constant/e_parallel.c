#include <omp.h>
#include <stdio.h>


/**
 * This function computes the Euler's number using a max number
 * of iterations.
 * 
 * const int n - iteration number
 */
long double e_constant(const int N)
{
    int i;
    long double e = 1;
#pragma omp parallel  
{
    unsigned long long int factorial = 1;
    // Set share and private values in parallel region
#pragma omp for reduction(+:e)
    for (i = 1; i <= N; i++)
    {
        // Computes factorial
        factorial *= i;
        // Computes e constant
        e += 1.0 / (double) factorial;
    }   
}
    return e;
}

int main(int argc, char const *argv[])
{
    const int N = 10;
    double start_time, run_time;

    // Use two threads
    omp_set_num_threads(2);

    // Run
    start_time = omp_get_wtime();
    long double e = e_constant(N);
    run_time = (omp_get_wtime() - start_time) * 1000000.0;

    printf("e is %.60Lf in %f microseconds with %d iterations\n", e, run_time, N);

    return 0;
}
