__kernel void saxpy_kernel(const float A,
                           __global float *x,
                           __global float *y,
                           __global float *result)
{
    // Get the index of the current element to be processed
    int i = get_global_id(0);
 
    // Do the operation
    result[i] = A*x[i] + y[i];
}