#include <stdio.h>
#include <stdlib.h>

#ifdef APPLE
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif


#define MAX_SOURCE_SIZE (0x100000)

// Matrix dimensions
#define N 4


/**
 * This function fills a matrix with natural numbers.
 *
 * Params:
 *     int* matrix - flatten matrix.
 */
void fill_matrix(int* matrix)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i*N + j] = rand() % 3;
        }
    }
}

/**
 * This function prints a matrix.
 *
 * Params:
 *     int* matrix - flatten matrix.
 */
void printm(int* matrix)
{
    printf("----------Matrix----------\n");

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // Print each column in a row
            printf("%d \t", matrix[i*N + j]);
        }

        printf("\n");
    }

    printf("--------------------------\n\n");
}


int main(int argc, char const *argv[])
{
    // Init random library
    srand(0);

    // Create matrix
    int* A = (int*) calloc(N*N, sizeof(int));
    int* B = (int*) calloc(N*N, sizeof(int));
    int* result = (int*) calloc(N*N, sizeof(int));

    printf("------------MA------------\n");
    fill_matrix(A);
    printm(A);

    printf("------------MB------------\n");
    fill_matrix(B);
    printm(B);

    // Load the kernel source code into the array source_str
    FILE* file;
    char* source_str;
    size_t source_size;

    // Read the kernel
    file = fopen("02-mat-mult/mat_mult.cl", "r");

    if (!file)
    {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }

    source_str = (char*) malloc(MAX_SOURCE_SIZE);
    source_size = fread(source_str, 1, MAX_SOURCE_SIZE, file);

    fclose(file);

    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_uint ret_num_platforms;
    cl_uint ret_num_devices;

    // Set up the Platform
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id,
                        &ret_num_devices);

    // Create an OpenCL context
    cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
    
    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

    // Create memory buffers on the device for each vector
    cl_mem A_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
                                      N*N*sizeof(int), NULL, &ret);
    cl_mem B_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
                                      N*N*sizeof(int), NULL, &ret);
    cl_mem result_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                           N*N*sizeof(int), NULL, &ret);

    // Copy the Buffer A and B to the device
    ret = clEnqueueWriteBuffer(command_queue, A_mem_obj, CL_TRUE, 0,
                               N*N*sizeof(int), A, 0, NULL, NULL);
    ret = clEnqueueWriteBuffer(command_queue, B_mem_obj, CL_TRUE, 0,
                               N*N*sizeof(int), B, 0, NULL, NULL);

    // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1, 
                                                (const char**) &source_str,
                                                (const size_t*) &source_size,
                                                &ret);

    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "mat_mult_kernel", &ret);

    int size = N;
    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(int), (void*) &size);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*) &A_mem_obj);
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*) &B_mem_obj);
    ret = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*) &result_mem_obj);

    // Execute the OpenCL kernel on the list
    // Process the entire lists
    size_t global_item_size[2] = {N, N};
    // Divide work items into groups of 64
    size_t local_item_size[2] = {N, N};

    ret = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL,
                                 &global_item_size, &local_item_size,
                                 0, NULL, NULL);

    // Read the memory buffer C on the device to the local variable C
    ret = clEnqueueReadBuffer(command_queue, result_mem_obj, CL_TRUE, 0,
                              N*N*sizeof(int), result, 0, NULL, NULL);


    // Print result
    printf("----------Result----------\n");
    printm(result);

    // Clean up
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(A_mem_obj);
    ret = clReleaseMemObject(B_mem_obj);
    ret = clReleaseMemObject(result_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);

    free(A);
    free(B);
    free(result);

    return 0;
}
