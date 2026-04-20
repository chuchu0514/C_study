//2023024050 추진성
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node;

void sort(Node *head); //정렬
void insert(Node **head, int data);//삽입
void printNode(Node *head);//출력
void delete(Node **head, int data);//삭제

int main(){

    Node *head = NULL;  
    FILE *fp = fopen("in.txt", "r");
    int num;
    fscanf(fp, "%d", &num);
    int *arr = malloc(sizeof(int)*num);
    for(int i = 0; i < num; i++){
        fscanf(fp, "%d", &arr[i]);
    }
    fclose(fp);

    for(int i = 0; i < num; i++){//연결리스트 입력 
        insert(&head, arr[i]);
    }

    sort(head);//정렬
    printf("Sorted List: ");
    printNode(head);//출력
    printf("\n");
    int del;
    //삭제 
    while (1) {
        printf("Enter del_num: ");
        scanf("%d", &del);
        if (del < 0) {
            printf("Quit\n"); 
            break; 
        }
        delete(&head, del);
        printf("Delete %d: ", del);
        printNode(head);
    }
    free(arr);
    Node *cur = head;
    while (cur != NULL) {//연결리스트 동적할당 해제 
        Node *tmp = cur->next;  
        free(cur);              
        cur = tmp;              
    }
    return 0;
}

void sort(Node *head) { //오름차순 정렬 
    int swapped;
    Node *cur;

    do {
        swapped = 0;
        cur = head;

        while (cur->next != NULL) {
            if (cur->data > cur->next->data) {
                int tmp = cur->data;
                cur->data = cur->next->data;
                cur->next->data = tmp;
                swapped = 1;
            }
            cur = cur->next;
        }
    } while (swapped);
}
void insert(Node **head, int data){
    Node * newnode = malloc(sizeof(Node));
    newnode -> data = data;
    newnode -> next = NULL;
    if(*head == NULL){
        *head = newnode;
        return;
    }
    
    Node *cur = *head;
    while (cur->next != NULL){
        cur = cur->next;
    }
    cur -> next = newnode;
    
}
void printNode(Node *head){
    Node *cur = head;
    while(cur != NULL){
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
    return;
}
void delete(Node **head, int data){
    Node * prev = NULL;
    Node * cur = *head;
    while(cur != NULL){
        if(cur->data == data){
            if(prev == NULL){//첫노드삭제
                *head = cur->next;
                free(cur);
                return;
            }
            else{
                prev->next = cur->next;
                free(cur);
                return;
            }
        }
        prev = cur;
        cur = cur->next;
    }


}