#include <stdio.h>
#include <string.h>

#define MAX_LEN 50

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    char str1[MAX_LEN], str2[MAX_LEN], str3[MAX_LEN], str4[MAX_LEN], temp[MAX_LEN];
    
   
    // scanf("%s") - reads until whitespace and takes single word
    
    
    printf("Enter your full name: \n\n");
    scanf("%s", str1);
    printf("Your name: \"%s\"\n", str1);
    printf("Length: %zu characters\n\n", strlen(str1));
    clear_input_buffer();  // Clear leftover input
    //scanf("%s",   temp);
    //printf("left over: %s\n", temp);
    
    // fgets() - reads entire line including spaces
    
    printf("Enter your full name again: ");
    fgets(str2, MAX_LEN, stdin);
    // Remove trailing newline if present
    str2[strcspn(str2, "\n")] = '\0';
    printf("Your name: \"%s\"\n", str2);
    printf("Length: %zu characters\n\n", strlen(str2));
    
    
    
    
    // scanf("%[^\n]") - reads until newline
    
    printf("Enter another sentence: ");
    scanf(" %[^\n]", str3);  // Note the space before % to skip whitespace
    printf("Sentence: \"%s\"\n", str3);
    printf("Length: %zu characters\n\n", strlen(str3));
    //clear_input_buffer();
    
    
    }
