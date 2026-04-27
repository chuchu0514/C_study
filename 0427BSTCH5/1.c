//2023024050 추진성
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node * left;
    int data;
    struct node* right;
}node;

node* create_node(int data);//노드생성
node* create_tree(int n);//트리생성 
int height(node* root);
int count_node(node* root);
int count_leafnode(node* root);
void inorder_traversal(node * root);
void levelorder_traversal(node* root);

int main(){
    int num;
    node * root = NULL;
    printf("Input numer : ");
    scanf("%d", &num);
    printf("\n");
    root = create_tree(num);
    printf("height: %d\n", height(root));
    printf("Node 개수: %d\n", count_node(root));
    printf("Leaf node개수: %d\n", count_leafnode(root));
    printf("Inorder traversal: ");
    inorder_traversal(root);
    printf("\n");
    printf("Levelorder traversal: ");
    levelorder_traversal(root);
    printf("\n");

}

node* create_node(int data) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

node* create_tree(int n) {
    node* root = create_node(n);
    
    if(n * n <= 100)
        root->left = create_tree(n * n);//재귀로 구현 
    if(2 * n <= 100)
        root->right = create_tree(2 * n);
    
    return root;
}

int height(node* root){
    if(root == NULL) return 0;
    int left = height(root->left);
    int right = height(root->right);
    return 1 + (left > right ? left : right);
}

int count_node(node* root){
    if(root == NULL) return 0;
    return 1 + count_node(root->left) + count_node(root->right);
}

int count_leafnode(node* root){
    if(root == NULL) return 0;
    if(root->left == NULL && root->right == NULL) return 1;
    return count_leafnode(root->left) + count_leafnode(root->right);

}

void inorder_traversal(node * root){
    if(root == NULL) return;

    inorder_traversal(root->left);
    printf("(%d) ", root->data);
    inorder_traversal(root->right);

}
void levelorder_traversal(node* root){
    node* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;  //루트넣기 

    while(front != rear){
        node* cur = queue[front++];  
        printf("(%d) ", cur->data);  

        if(cur->left != NULL)        
            queue[rear++] = cur->left;
        if(cur->right != NULL)       
            queue[rear++] = cur->right;
    }

}