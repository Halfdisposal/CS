#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void xstrcpy(char* copy, const char* string)//Function that copies `string' to `copy'
{
    int i = 0, len;

      
    while(*string != '\0')
    {
       *copy = *string;

       copy++;
       string++;

       
    }

    *copy = '\0';

    //string[0] = 'I'; //Not allowed

    
}

int main()
{
    char* name = "Kripa", copy[20];
    

    xstrcpy(copy, name);

    printf("The copy of %s is %s\n", name, copy);

    

	return 0;
}
