//2023024050 추진성
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
}node;

node* insert(node* root, int data);
void print_inorder(node* root);
int print_func(node* root, int num, int* arr, int count, int found);

int main(){

    FILE* fp = fopen("in.txt","r");
    node* root = NULL;
    int size;
    int data;
    int num;
    int arr[100];
    fscanf(fp,"%d", &size);
    for(int i = 0; i < size; i++){
        fscanf(fp, "%d", &data);
        root = insert(root, data);
    }
    printf("Inorder traversal:\n");
    print_inorder(root);
    printf("\n\n");

        do{
        printf("input number: ");
        scanf("%d", &num);
        if(num >= 0){

        int found = print_func(root, num, arr, 0, 1);
            if(!found){
                root = insert(root, num);
                print_func(root, num, arr, 0, 0);
            }
        }
        else{
            printf("exit");
            break;
        }
    }while(1);

    fclose(fp);
    return 0;
}

node* insert(node* root, int data){
    if(root == NULL){
        node* newnode = (node*)malloc(sizeof(node));
        newnode->data = data;
        newnode->left = NULL;
        newnode->right = NULL;
        root = newnode;
        return root;
    }

    if(data < root->data){
        root->left = insert(root->left, data);
    }
    else{
        root->right = insert(root->right, data);
    }
    return root;
}
void print_inorder(node* root){
    if(root == NULL){
        return;
    }
    print_inorder(root->left);
    printf("%d ", root->data);
    print_inorder(root->right);
}
int print_func(node* root, int num, int *arr, int count, int found){

    if(root == NULL){
        printf("Fail: ");
        return 0;
    }
    if(root-> data == num){
        arr[count] = root->data;
        if(found){
            printf("Success: ");
        }
        for(int i = 0; i < count + 1; i++){
            printf("%d ", arr[i]);
        }
        printf("\n");
        return 1;
    }
    else if(num < root->data){
        arr[count] = root->data;
        count++;
        return print_func(root->left, num, arr, count, found);
    }
    else{
        arr[count] = root->data;
        count++;
        return print_func(root->right, num, arr, count, found);
    }
}