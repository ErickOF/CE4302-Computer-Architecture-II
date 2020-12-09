#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef APPLE
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif


#define MAX_SOURCE_SIZE (0x100000)


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

int main(int argc, char const *argv[])
{
    // Times
    clock_t start_time, end_time;

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
    
        // Load the kernel source code into the array source_str
        FILE *file;
        char *source_str;
        size_t source_size;

        // Read the kernel
        file = fopen("01-saxpy/saxpy.cl", "r");

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
        cl_mem x_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
                                        N*sizeof(float), NULL, &ret);
        cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
                                        N*sizeof(float), NULL, &ret);
        cl_mem y_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                        N*sizeof(float), NULL, &ret);

        // Copy the Buffer x and b to the device
        ret = clEnqueueWriteBuffer(command_queue, x_mem_obj, CL_TRUE, 0,
                                N*sizeof(float), x, 0, NULL, NULL);
        ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0,
                                N*sizeof(float), b, 0, NULL, NULL);

        // Create a program from the kernel source
        cl_program program = clCreateProgramWithSource(context, 1, 
                                                    (const char**) &source_str,
                                                    (const size_t*) &source_size,
                                                    &ret);

        // Build the program
        ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

        // Create the OpenCL kernel
        cl_kernel kernel = clCreateKernel(program, "saxpy_kernel", &ret);

        // Set the arguments of the kernel
        ret = clSetKernelArg(kernel, 0, sizeof(float), (void*) &A);
        ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*) &x_mem_obj);
        ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*) &b_mem_obj);
        ret = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*) &y_mem_obj);

        // Execute the OpenCL kernel on the list
        // Process the entire lists
        size_t global_item_size = N;
        // Divide work items into groups of 64
        size_t local_item_size = 64;

        start_time = clock();

        ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,
                                    &global_item_size, &local_item_size,
                                    0, NULL, NULL);

        end_time = clock();

        // Read the memory buffer C on the device to the local variable C
        ret = clEnqueueReadBuffer(command_queue, y_mem_obj, CL_TRUE, 0,
                                N*sizeof(float), y, 0, NULL, NULL);

        printf("Saxpy in GPU with %ld value in %lf seconds\n\n", N,
               (double) (end_time - start_time) / CLOCKS_PER_SEC);

        // Clean up
        ret = clFlush(command_queue);
        ret = clFinish(command_queue);
        ret = clReleaseKernel(kernel);
        ret = clReleaseProgram(program);
        ret = clReleaseMemObject(x_mem_obj);
        ret = clReleaseMemObject(b_mem_obj);
        ret = clReleaseMemObject(y_mem_obj);
        ret = clReleaseCommandQueue(command_queue);
        ret = clReleaseContext(context);

        // Free memory
        free(x);
        free(b);
        free(y);
    }

    return 0;
}
