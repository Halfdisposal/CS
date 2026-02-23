#include <stdio.h>

int fact(int n) //Iterative version
{
    int i, f = 1;

    for(i = 1 ; i <= n; i++)
    {
        f = f*i;
    }

    return f;

}

int fact_recursive(n) //Recursive version
{
    int x;

    if(n == 1)
    {
        printf("Base condition return: n = %d %u\n", n, &n);
        return 1;
    }
    else
    {
        printf("n = %d: before recursive call! %u\n", n, &n);
        x = n*fact_recursive(n-1);
        printf("n = %d: after returning from call! %u\n", n, &n);
        printf("Current value of factorial (x) = %d\n", x);

        return x;
    }
    
}


int main() {

   int n = 4, fct, fct_rec;

   printf("Call from main\n");

   fct = fact(n);

   fct_rec = fact_recursive(n);

   printf("Return to main\n");

   printf("Factorial(%d) = %d (recursive)\n", n, fct_rec);

   printf("Factorial(%d) = %d (iterative)\n", n, fct);
   return 0;
}
