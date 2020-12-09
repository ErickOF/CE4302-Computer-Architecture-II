__kernel void mat_mult_kernel(const int size,
                              __global int* A,
                              __global int* B,
                              __global int* result)
{
    // Get the index of the current element to be processed
    int i = get_global_id(0);
    int j = get_global_id(1);

    for (int k = 0; k < size; k++)
    {
        result[i*size + j] += A[i*size + k] * B[k*size + j];
    }
}