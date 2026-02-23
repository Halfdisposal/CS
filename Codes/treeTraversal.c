#include <stdio.h>
#include <stdlib.h>


// Define the node structure
typedef struct node {
    int key;    
    struct node* left;
    struct node* right;
} node;


void inorder(node* x) {
    if (x != NULL) {
        inorder(x->left);
        printf("%d\t", x->key);
        inorder(x->right);
    }

}


int main() {
    node* str1 = NULL;
    str1 = (node*)malloc(sizeof(node));

    str1->key = 10;
    str1->left = NULL;
    str1->right = NULL;
    
    node* str2 = (node*)malloc(sizeof(node));
    str2->key = 20;
    str2->left = NULL;
    str2->right = NULL;

    node* str3 = (node*)malloc(sizeof(node));
    str3->key = 30;
    str3->left = NULL;
    str3->right = NULL;

    node* str4 = (node*)malloc(sizeof(node));
    str4->key = 40;
    str4->left = NULL;
    str4->right = NULL;

    str1->left = str2;
    str1->right = str3;

    str2 ->left = str4;

    inorder(str1);

}