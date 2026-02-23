#include<stdio.h>

void main()
{

	int A[3][3] = {{2, 1, 2}, {3, 1, 3}, {2, 5, 1}}, B[3][2] = {{2, 5}, {3, 1}, {7, 4}}, Prod[10][10] = {}, nr1 = 3, nc1 = 3, nr2 = 3, nc2 = 2, nr3, nc3, i, j, k;

    if(nc1 != nr2)
    {
        printf("Invalid multiplication!\n");
    }
    else
    {
        for(i = 0 ; i < nr1 ; i++)
        {
            for(j = 0 ; j < nc2 ; j++)
            {
                //Prod[i][j] = 0;
                for(k = 0 ; k < nc1 ; k++)
                {
                    Prod[i][j] += A[i][k]*B[k][j];

                    
                }
                
            }
        }

        printf("The product:\n");

        nr3 = nr1;
        nc3 = nc2;

        for(i = 0 ; i < nr1 ; i++)
        {
            for(j = 0 ; j < nc2 ; j++)
            {
                printf("%d ", Prod[i][j]);
            }
            printf("\n");
        }    

    }
    

    
    

	
    
    	
    
}



