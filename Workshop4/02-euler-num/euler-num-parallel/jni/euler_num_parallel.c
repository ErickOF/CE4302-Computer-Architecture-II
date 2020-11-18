#include <omp.h>
#include <stdio.h>


/**
 * This function computes the Euler's number using a max number
 * of iterations.
 * 
 * const long long int n - iteration number
 */
long double e_constant(const long long int N)
{
    int i;
    long double e = 1;

    #pragma omp parallel
    {
        double factorial = 1;

        // Set share and private values in parallel region
        #pragma omp for reduction(+:e)
        for (i = 1; i <= N; i++)
        {
            // Computes factorial
            factorial *= (double) i;
            // Computes e constant
            e += 1.0 / factorial;
        }   
    }

    return e;
}

int main(int argc, char const *argv[])
{
    for (int i = 1; i <= 6; i++)
    {
        const long long int N = i * 100000000L;
        double start_time, run_time;

        // Use two threads
        omp_set_num_threads(2);

        // Run
        start_time = omp_get_wtime();
        long double e = e_constant(N);
        run_time = (omp_get_wtime() - start_time);

        printf("e is %.60Lf in %f seconds with %lld iterations\n", e, run_time, N);
    }

    return 0;
}

