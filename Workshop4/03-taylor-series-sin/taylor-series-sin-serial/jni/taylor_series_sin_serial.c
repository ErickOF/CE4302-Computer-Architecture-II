#include <math.h>
#include <omp.h>
#include <stdio.h>


/**
 * This function computes the Taylor series for sin function using a
 * max number of iterations.
 *
 * const long long int n - iteration number,
 * float x               - value of the function to approximate.
 */
long double taylor_series_sin(const long long int N, float x)
{
    int i;
    long double sin_x = x;
    double fact = 1;

    for (i = 1; i <= N; i++)
    {
        // Computes factorial
        fact *= (double) (2 * i + 1) * (2 * i);
        // Computes sin(x) constant
        sin_x += pow(-1, i) * pow(x, 2 * i + 1) / fact;
    }
    
    return sin_x;
}

int main(int argc, char const *argv[])
{
    const long long int N = 10000000L;
    double start_time, run_time;
    float x = 0.1;

    // Run
    start_time = omp_get_wtime();

    long double sin_x = taylor_series_sin(N, x);

    run_time = (omp_get_wtime() - start_time);

    printf("sin(%f) is %.60Lf in %f seconds with %lld iterations\n", x, sin_x, run_time, N);

    return 0;
}

