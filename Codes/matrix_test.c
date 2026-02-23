#include<stdio.h>

int main()
{
	int matA[2][3], matB[2][3], matSum[2][3], i, j;
	
	//Taking input...A...
	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < 3; j++)
		{
			printf("Element - (%d %d): \n", i, j);
			scanf("%d", &matA[i][j]);
		}
	}	
	
	//Printing...A...
	printf("Matrix A: \n");
	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < 3; j++)
		{
			printf("%d ", matA[i][j]);
			
		}
		printf("\n");
	}	


	//Taking input...B...
	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < 3; j++)
		{
			printf("Element - (%d %d): \n", i, j);
			scanf("%d", &matB[i][j]);
		}
	}	
	
	//Printing...B...
	printf("Matrix B: \n");
	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < 3; j++)
		{
			printf("%d ", matB[i][j]);
			
		}
		printf("\n");
	}
	
	
	//Summing...
	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < 3; j++)
		{
			matSum[i][j] = matA[i][j] + matB[i][j];
		}
	}	
	
	//Printing...Sum...
	printf("The Sum: \n\n");
	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < 3; j++)
		{
			printf("%d ", matSum[i][j]);
			
		}
		printf("\n");
	}
	
		
}
