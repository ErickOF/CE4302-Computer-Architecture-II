#include <emmintrin.h> 
#include <smmintrin.h>

#include <stdio.h>


int main()
{
	int data;
	printf("Probando SSE \n");

	__m128i oddVector = _mm_set_epi32(1, 5, 9, 13);
	__m128i evenVector = _mm_set_epi32(12, 14, 16, 18);

	__m128i result = _mm_sub_epi32(evenVector, oddVector); // result = evenVector - oddVector

	printf("Result *********************** \n");
	
	data = 0;

	data = _mm_extract_epi32(result,0);
	printf("%d \t", data);

	data = _mm_extract_epi32(result,1);
	printf("%d \t", data);

	data = _mm_extract_epi32(result,2);
	printf("%d \t", data);

	data = _mm_extract_epi32(result,3);
	printf("%d \t", data);

	printf("\n");

	return 0;
}
