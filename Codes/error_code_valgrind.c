#include<stdlib.h>

void f()
{
	int *x = (int*)malloc(10*sizeof(int));
	//x[10] = 5;
	free(x);

}

int main()
{
	f();
}
