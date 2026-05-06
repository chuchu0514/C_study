//2023024050 추진성
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
}node;

void insert(node** head, int data);
void print_arr(int** arr, int size);
void print_linkedarr(node* head);
int count_degree(node* head);

int main(){

    FILE *fp = fopen("in.txt", "r");
    int size, edge_count;
    fscanf(fp, "%d %d", &size, &edge_count);
    int num1, num2;

    node** linkedarr = (node**)malloc(size * sizeof(node*)); //연결인접리스트 동적할당
    for(int i = 0; i < size; i++){
        linkedarr[i] = NULL;
    }
    node** inv_linkedarr = (node**)malloc(size * sizeof(node*));//inverse연견인접리스트 동적할당
    for(int i = 0; i < size; i++){
        inv_linkedarr[i] = NULL;
    }
    int** arr = (int**)malloc(sizeof(int*)*size); //인접행렬 동적할당 
    for(int i = 0; i < size; i++){
        arr[i] = (int*)malloc(sizeof(int)*size);
    }

    for(int i = 0; i < size; i++){//인접 행렬 0으로 초기화 
        for(int j = 0; j < size; j++){
            arr[i][j] = 0;
        }
    }

    for(int i = 0; i < edge_count; i++){
        fscanf(fp, "%d %d", &num1, &num2);
        arr[num1][num2] = 1; //인접 행렬 1
        insert(&linkedarr[num1], num2);//인접리스트 
        insert(&inv_linkedarr[num2], num1);//역인접리스트
    }

    printf("(1) Adjacency matrix\n");
    print_arr(arr, size);

    printf("(2) Linked adjacency list\n");
    for(int i = 0; i < size; i++){
        printf("[ %d]", i);
        print_linkedarr(linkedarr[i]);
    }
    printf("\n\n");

    printf("(3) Inverse adjacency list\n");
    for(int i = 0; i < size; i++){
        printf("[ %d]", i);
        print_linkedarr(inv_linkedarr[i]);
    }
    printf("\n\n");

    printf("(4) In degree\n");
        for(int i = 0; i < size; i++){
        printf("[ %d] %d\n", i, count_degree(inv_linkedarr[i]));
    }
    printf("\n\n");

    printf("(5) Outdegree\n");
        for(int i = 0; i < size; i++){
        printf("[ %d] %d\n", i, count_degree(linkedarr[i]));
    }
    printf("\n\n");

    fclose(fp);

    for(int i = 0; i < size; i++){
        node* cur = linkedarr[i];
        while(cur != NULL){
            node* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(linkedarr);  

    for(int i = 0; i < size; i++){
        node* cur = inv_linkedarr[i];
        while(cur != NULL){
            node* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(inv_linkedarr);

    for(int i = 0; i < size; i++){
        free(arr[i]);
    }
    free(arr);
}

void insert(node** head, int data){
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = data;

    if(*head == NULL){
        newnode->next = NULL;
        *head = newnode;
        return;
    }

    newnode->next = *head;
    *head = newnode;
    return;
}

void print_arr(int** arr, int size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");

}
void print_linkedarr(node* head){
    node* cur = head;
    while(cur != NULL){
        printf("  %d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

int count_degree(node* head){
    node* cur = head;
    int count = 0;
    while(cur != NULL){
        cur = cur->next;
        count++;
    }
    return count;
}