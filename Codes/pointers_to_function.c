#include<stdio.h>


void print()
{
	printf("print is called!\n");
    	
}

int add(int a, int b)
{
	printf("add is called!\n");
    	return (a + b);
}

int add_v2(int a, int b)
{
	printf("add v2 is called!\n");
    	return (a + b + 5);
}
 
int  printSum(int (*f)(), int a, int b) //Look into qsort() in stdlib.h for similar application
{
	printf("printSum called!\n");
	return ((*f)(a,b) + 1);																					

}
int main()
{
    int (*f)(int, int); //(*f)() also is OK
    
    
    void (*f1)();

    
    f1 = print;
    //f1();
    
    f = add;
    
    //printf("%u\n", f);

    //printf("Sum = %d\n", (*f)(4, 5));
    //printf("Sum = %d\n", f(4, 5));
    //printf("Sum = %d\n", printSum(add, 4, 5));
    //printf("Sum = %d\n", printSum(f, 4, 5));
    printf("Sum = %d\n", printSum(add_v2, 4, 5));


	return 0;
}
