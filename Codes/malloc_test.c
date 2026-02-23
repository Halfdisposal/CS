#include <stdio.h>
#include <stdlib.h>

void main()
{
    int *numbers = (int*)malloc(5 * sizeof(int));
    int i;
    
    if (numbers == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    printf("Initial allocation starting memory address: %u\n\n", numbers);
    
    printf("Initial array of 5 elements:\n");
    for (i = 0; i < 5; i++) {
        numbers[i] = i * 10;
        printf("numbers[%d] = %d\n", i, numbers[i]);
    }
    
    // Realloc to expand to 10 integers
    printf("\nReallocating to 10 elements...\n");
    int *temp = (int*)realloc(numbers, 10 * sizeof(int));
    if (temp == NULL) {
        printf("Reallocation failed! Keeping original array.\n");
    } else {
        numbers = temp;
        printf("Reallocation successful!\n");
       
       printf("After relocation expand, starting memory address: %u\n\n", numbers); 
       
        // Initialize new elements
        for (int i = 5; i < 10; i++) {
            numbers[i] = i * 10;
        }
        
        printf("Expanded array:\n");
        for (i = 0; i < 10; i++) {
            printf("numbers[%d] = %d\n", i, numbers[i]);
        }
    }
    
    // Realloc to shrink to 3 integers
    printf("\nShrinking to 3 elements...\n");
    temp = (int*)realloc(numbers, 3 * sizeof(int));
    if (temp == NULL) {
        printf("Shrinking failed!\n");
    } else {
        numbers = temp;
        printf("Array after shrinking:\n");
        for (int i = 0; i < 3; i++) {
            printf("numbers[%d] = %d\n", i, numbers[i]);
        }
    }
    
     printf("After relocation shrink, starting memory address: %u\n\n", numbers); 
    
    free(numbers);
    printf("Memory freed.\n");



}
