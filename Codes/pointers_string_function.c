#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char* reverseString(char * string)//Function that returns the reversed version of string
{
    char *reversed;
    int i = 0, len;
    
    //string[0] = 'l';
    //printf("%c\n", string[0]);

    len = strlen(string);

    reversed = (char*)malloc((len + 1)*sizeof(char));//Allocated memory for the reversed string

   
    while(string[i] != '\0')
    {
        reversed[len - 1 - i] = string[i];
        
        i++;
    }

    reversed[i] = '\0';
    
    
    return reversed;
}

int main()
{
    char* name = "Kripa";

    printf("Reversed version of %s is %s\n", name, reverseString(name));


	return 0;
}
