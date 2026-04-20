//16분
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
}node;

void insert(node ** head, int data);
void frontinsert(node** head, int data);
void print_list(node* head);
void merge(node** head1, node** head2);

int main(){
    node* head1 = NULL;
    node* head2 = NULL;
    int num;
    FILE *fp = fopen("a1.txt", "r");
    while(fscanf(fp,"%d", &num) != EOF){
        if(num % 2 == 0){
            insert(&head1, num);
        }
        else{
            frontinsert(&head2, num);
        }
    }
    fclose(fp);
    printf("L1: ");
    print_list(head1);
    printf("L2: ");
    print_list(head2);
    printf("Merged: ");
    merge(&head1, &head2);

}

void insert(node ** head, int data){
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data =data;
    newnode->next = NULL;

    if(*head == NULL){
        *head = newnode;
        return;
    }
    node* cur = *head;
    while(cur->next != NULL){
        cur= cur->next;
    }
    cur->next = newnode;
    return;
}

void frontinsert(node** head, int data){
    node* newnode = (node*)malloc(sizeof(node));

    if(*head == NULL){
        newnode->data =data;
        newnode->next = NULL;
        *head = newnode;
        return;
    }

    newnode->data =data;
    newnode->next = *head;

    *head = newnode;

}

void merge(node** head1, node** head2){
    node* cur = *head1;

    while(cur->next != NULL){
        cur = cur->next;
    }
    cur->next = *head2;

    cur = *head1;

    while(cur != NULL){
    if(cur->data % 3 == 0)
        printf("%d ", cur->data);
    cur = cur->next;
    }
}

void print_list(node* head){
    node * cur = head;
    while(cur != NULL){
        printf("%d ", cur->data);
        cur= cur->next;
    }
    printf("\n");
}
