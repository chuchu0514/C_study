#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
}node;
void preorder(node* root);
node* insert(node* root, int data);
int count_bst(node* root);

int main(){
    FILE *fp =fopen("input.txt", "r");
    int size, num;
    int count;
    fscanf(fp, "%d", &size);
    node* root = NULL;
    for(int i = 0; i < size; i++){
        fscanf(fp, "%d", &num);
        root = insert(root, num);
    }
    preorder(root);
    node* cur = root;
    int k;
    scanf("%d", &k);
    while(cur != NULL &&cur->data != k){
        if(cur->data < k){
            cur= cur->right;
        }
        else if(cur->data > k){
            cur = cur->left;
        }
    }
    
    count = count_bst(cur);
    
    printf("%d", count);
    return 0;
}

node* insert(node* root, int data){
    if(root == NULL){
        node* newnode = malloc(sizeof(node));
        newnode->data = data;
        newnode->left = NULL;
        newnode->right = NULL;
        return newnode;
    }
    if(data < root->data){
        root -> left = insert(root->left, data);
    }
    else{
        root->right = insert(root->right, data);
    }
    return root;
}

void preorder(node* root){
    if(root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

int count_bst(node* root){
    if(root == NULL) return 0;
    int left = count_bst(root->left);
    int right = count_bst(root->right);

    return 1 + left + right;
}