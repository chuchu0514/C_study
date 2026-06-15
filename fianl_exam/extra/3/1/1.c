#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
}node;

node* insert(node* root, int data);
void inorder(node* root);
node* delete(node* root, int k);
node* findMin(node* root);
int main(){
    FILE *fp = fopen("input.txt", "r");
    int size, num;
    node* root= NULL;
    fscanf(fp, "%d", &size);
    for(int i = 0; i < size; i++){
        fscanf(fp, " %d", &num);
        root = insert(root, num);
    }
    int k;
    fscanf(fp, "%d", &k);
    root = delete(root, k);
    inorder(root);

    fclose(fp);
    return 0;
}
node* findMin(node* root){
    while(root->left != NULL) root = root->left;
    return root;
}

void inorder(node* root){
    if(root ==NULL) return;
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}
node* insert(node* root, int data){
    if(root ==NULL){
        node* newnode = malloc(sizeof(node));
        newnode->data = data;
        newnode->left = NULL;
        newnode->right = NULL;
        return newnode;
    }
    if(data < root->data){
        root->left = insert(root->left, data);
    }
    else{
        root->right = insert(root->right, data);
    }
    return root;
}

node* delete(node* root, int k){
    if(root == NULL) return NULL;

    if(root->data > k){
        root->left = delete(root->left, k);
    }
    else if(root->data < k){
        root->right= delete(root->right, k);
    }
    else{
        // 찾음. 세 경우로 나눔.
        if(root->left == NULL && root->right == NULL){   // (1) leaf
            free(root);
            return NULL;
        }
        else if(root->left == NULL){                     // (2) 오른쪽 자식만
            node* child = root->right;
            free(root);
            return child;
        }
        else if(root->right == NULL){                    // (2) 왼쪽 자식만
            node* child = root->left;
            free(root);
            return child;
        }
        else {                                           // (3) 자식 둘
            node* successor = findMin(root->right);       // 오른쪽 최소값
            root->data = successor->data;                 // 값만 복사
            root->right = delete(root->right, successor->data);  // 그 노드 삭제
        }
    }
    return root;

}