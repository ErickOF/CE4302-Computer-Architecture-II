/**
 * Program that searches for the max element in each column of a
 * matrix and stores it in a vector. The matrix corresponds to 4x3 and
 * is made up of integers (32-bits). For this program we want all the
 * numbers to be positive to make the comparison. The user enters all
 * the numbers as parameters and must print the three rows, as well as
 * the result of each greater.
 */
#include <emmintrin.h>
#include <smmintrin.h>

#include <stdio.h>

// Matrix dimensions
#define ROWS 3
#define COLS 4


/**
 * This function fills a matrix with natural numbers.
 *
 * Params:
 *     __m128i matrix[] - array of vectors.
 */
void fill_matrix(__m128i matrix[ROWS])
{
    printf("------Getting values------\n");

    for (int i = 0; i < ROWS; i++)
    {
        // To store row values
        int values[] = {0, 0, 0, 0};
        // To store each value
        int value;

        for (int j = 0; j < COLS; j++)
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
 * This function prints a matrix.
 *
 * Params:
 *     __m128i matrix[] - array of vectors.
 */
void printm(__m128i matrix[ROWS])
{
    printf("----------Matrix----------\n");

    for (int i = 0; i < ROWS; i++)
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

/**
 * This function returns the max value of each column of a matrix.
 *
 * Params:
 *     __m128i matrix[] - array of vectors.
 *
 * Returns:
 *     A vector representing the max value of each column.
 */
__m128i get_max_values(__m128i matrix[ROWS])
{
    // Max values vector
    __m128i max_values = _mm_set_epi32(0, 0, 0, 0);

    for (int i = 0; i < ROWS; i++)
    {
        max_values = _mm_max_epi32(max_values, matrix[i]);
    }

    return max_values;
}

int main(int argc, char const *argv[])
{
    // Create matrix
    __m128i matrix[ROWS];

    fill_matrix(matrix);
    printm(matrix);

    // Get max number of each column
    __m128i max_values = get_max_values(matrix);

    // Print result
    printf("----------Result----------\n");
	printf("%d \t", _mm_extract_epi32(max_values, 0));
    printf("%d \t", _mm_extract_epi32(max_values, 1));
    printf("%d \t", _mm_extract_epi32(max_values, 2));
    printf("%d \t\n", _mm_extract_epi32(max_values, 3));
    printf("--------------------------\n");

    return 0;
}
