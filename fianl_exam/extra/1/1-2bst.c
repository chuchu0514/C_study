#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    struct node* left;
    int data;
    struct node* right;
}node;

void inorder(node* root);
node* insert(node* root, int data);
int issame(node* r1, node* r2);

int main(){
    FILE * fp = fopen("input2.txt", "r");
    int size1, size2;
    int num;
    fscanf(fp, "%d", &size1);
    node* root1 = NULL;
    for(int i = 0; i < size1; i++){
        fscanf(fp, "%d", &num);
        root1 = insert(root1, num);
    }
    inorder(root1);
    printf("\n");
    fscanf(fp, "%d", &size2);
    node* root2 = NULL;
    for(int i = 0; i < size2; i++){
        fscanf(fp, "%d", &num);
        root2 = insert(root2, num);
    }
    inorder(root2);
    printf("\n");
    int i = issame(root1, root2);
    if(i){
        printf("SAME");
    }
    else{
        printf("DIFFERENT");
    }
}

void inorder(node* root){
    if(root == NULL){
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int issame(node* r1, node* r2){
    if(r1 == NULL && r2 == NULL) return 1;   // 둘 다 비었으면 같음
    if(r1 == NULL || r2 == NULL) return 0;   // 한쪽만 비었으면 다름
    if(r1->data != r2->data) return 0;       // 값이 다르면 다름

    // 왼쪽도 같고 오른쪽도 같아야 전체가 같다 → 결과를 return으로 이어줌
    return issame(r1->left, r2->left) && issame(r1->right, r2->right);
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