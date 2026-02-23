#include<stdio.h>

void f1()
{
	printf("Hi...we are in f1\n");
}

void f2()
{
	printf("Hi...we are in f2\n");
	f1();

}


void main()
{
	f2();

}

