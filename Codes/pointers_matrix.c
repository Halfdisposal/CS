#include<stdio.h>
#include<string.h>

void display2D(int arr[][3], int rows)
{
	int i, j;
	printf("\n\nIn display2D:\n\n");
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < 3; j++)
		{
			printf("%d ", arr[i][j]);
		}
	printf("\n");
	}
}

void display1Dptr(int *arr, int rows, int cols)
{
	int i, j;
	printf("\n\nIn display1Dptr:\n\n");
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			printf("%d ", *(arr + i*cols + j));
		}
	printf("\n");
	}
}

void display1Dptr2ptr(int **arr, int rows, int cols) //works for dynamically allocated 2D arrays
{
	int i, j;
	
	printf("\nThe matrix, in pointer to pointer notation:\n\n");
	
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			//printf("%d ", arr[i][j]);
			printf("%u %d ", (*(arr+i) + j), *(*(arr+i) + j));
		}
		printf("\n");
	}

}


int main()
{
    int a[2][3] = {{5, 6, 1}, {2, 9, 7}}, *p, (*q)[3], *r, i , j, noOfRows = 2, noOfCols = 3;

    

    printf("Printing the element-wise addresses:\n");

    for(i = 0; i < noOfRows; i++)
    {
        for(j = 0; j < noOfCols; j++)
        {
            printf("%u ", &a[i][j]);
        }
        printf("\n");
    }

   	
    printf("\n\n");

    printf("Pointers to 0th row, 1st row: %u %u\n", &a[0][0], &a[1][0]);//Pointers to the 0th row, 1st row
    printf("Pointers to 0th row, 1st row: %u %u\n", *a, *(a + 1));
   
    printf("Pointers to the (0,1)th, (1,1)th elements: %u %u\n", &a[0][1], &a[1][1]);//Pointers to the (0,1)th, (1,1)th elements
    printf("Pointers to the (0,1)th, (1,1)th elements: %u %u\n", *(a + 0) + 1, *(a + 1) + 1);
    //printf("Pointers to the %u\n", *(*(a+1)+1));
	
    printf("\n\n");

    p = &a[0][0]; //p = a also works

    printf("Using a in pointer form...\n\n");

    for(i = 0; i < noOfRows; i++)
    {
        for(j = 0; j < noOfCols; j++)
        {
            printf("%d ", *(*(a + i) + j));
        }
        printf("\n");
    }

    printf("\n\n");

    printf("Using p...\n\n");

    for(i = 0; i < noOfRows; i++)
    {
        for(j = 0; j < noOfCols; j++)
        {
            printf("%d ", *(p + i*noOfCols + j));
        }
        printf("\n");
    }
    
    display2D(a, 2);
    
    display1Dptr(&a[0][0], 2, 3);
    
    //display1Dptr2ptr(a, 2, 3);
    
    
    
/*
    printf("\n\n");
    
    printf("Using q..\n\n");

    q = a;

    for(i = 0; i < noOfRows; i++)
    {
        r = q + i;
        for(j = 0; j < noOfCols; j++)
        {
            printf("%d ", *(r + j));
        }
        printf("\n");
    }

    printf("\n\n");

    */



	return 0;
}
