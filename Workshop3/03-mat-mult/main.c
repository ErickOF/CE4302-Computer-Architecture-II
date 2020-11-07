/**
 * Program that performs the multiplication of a vector of 4 integers
 * by a 4x4 matrix.
 */
#include <emmintrin.h>
#include <smmintrin.h>

#include <stdio.h>

// Matrix and vector dimensions
#define N 4


/**
 * This function fills a matrix with natural numbers.
 *
 * Params:
 *     __m128i matrix[] - array of vectors.
 */
void fill_matrix(__m128i matrix[N])
{
    printf("------Getting values------\n");

    for (int i = 0; i < N; i++)
    {
        // To store row values
        int values[] = {0, 0, 0, 0};
        // To store each value
        int value;

        for (int j = 0; j < N; j++)
        {
            // Get the value
            printf("Value [%d, %d]: ", i, j);
            scanf("%d", &value);
            values[j] = value;
        }

        // Create a vector/row
        matrix[i] = _mm_set_epi32(values[3], values[2], values[1], values[0]);
    }

    printf("--------------------------\n\n");
}

/**
 * This function creates a vector of natural numbers.
 *
 * Returns:
 *     A vector of natural numbers.
 */
__m128i create_vector()
{
    // To store row values
    int values[] = {0, 0, 0, 0};
    // To store each value
    int value;

    printf("------Getting values------\n");

    for (int i = 0; i < N; i++)
    {
        // Get the value
        printf("Value [%d]: ", i);
        scanf("%d", &value);
        values[i] = value;
    }

    // Create a vector
    __m128i vector = _mm_set_epi32(values[3], values[2], values[1], values[0]);

    printf("--------------------------\n\n");

    return vector;
}

/**
 * This function multiply a matrix by a vector.
 *
 * Params:
 *     __m128i result[] - array of vectors.
 *     __m128i matrix[] - array of vectors.
 *     __m128i vector   - vector of natural numbers.
 */
void mult_matrix_vector(__m128i result[N], __m128i matrix[N], __m128i vector)
{
    for (int i = 0; i < N; i++)
    {
        // Compute multiplication
        result[i] = _mm_mullo_epi32(matrix[i], vector);
    }
}

/**
 * This function prints a matrix.
 *
 * Params:
 *     __m128i matrix[] - array of vectors.
 */
void printm(__m128i matrix[N])
{
    printf("----------Matrix----------\n");

    for (int i = 0; i < N; i++)
    {
        // Print each column in a row
	    printf("%d \t", _mm_extract_epi32(matrix[i], 0));
        printf("%d \t", _mm_extract_epi32(matrix[i], 1));
        printf("%d \t", _mm_extract_epi32(matrix[i], 2));
        printf("%d \t", _mm_extract_epi32(matrix[i], 3));
        printf("\n");
    }

    printf("--------------------------\n\n");
}



int main(int argc, char const *argv[])
{
    // Create matrix
    __m128i matrix[N], result[N];
    fill_matrix(matrix);
    printm(matrix);

    // Create vector
    __m128i vector = create_vector();

    // Multiply matrix by vector
    mult_matrix_vector(result, matrix, vector);

    // Print result
    printf("----------Result----------\n");
    printm(result);

    return 0;
}
