#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Comparison function for integers in ascending order
int compare_ascending(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);//Interpretation: a-b < 0 (this is returned) ==> a comes before b in the sorted array; > 0 ==> a comes after b
}

// Comparison function for integers in descending order
int compare_descending(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

void print_array(int arr[], int n) {
	int i;
	printf("The array:\n\n");
	for (i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n\n");
}

int main()
{
	int a[] = {4, 1, 3, 2, 8, 5};
	
	int array_len = sizeof(a) / sizeof(a[0]);
	
	print_array(a, array_len);
	
	qsort(a, array_len, sizeof(int), compare_ascending);
	
	print_array(a, array_len);
	
	
	
	

}
