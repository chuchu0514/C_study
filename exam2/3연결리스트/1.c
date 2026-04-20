//14분
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
}node;

void insert(node** head, int data);
int count_value(node* head, int input);

int main(){
    FILE *fp = fopen("a1.txt", "r");
    int num;
    node * head = NULL;

    while(fscanf(fp, "%d ", &num) != EOF){
        insert(&head, num);
    }
    int input;
    int value;
    do{
        printf("input: ");
        scanf("%d", &input);
        if(input == -1)break;
        value = count_value(head, input);
        printf("%d appears %d times\n", input, value);

    }while(1);

    fclose(fp);
    return 0;

}

void insert(node** head, int data){
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = data;
    newnode->next = NULL;

    if(*head == NULL){
        *head = newnode;
        return;
    }
    node* cur = *head;
    while(cur->next != NULL){
        cur = cur->next;
    }
    cur->next = newnode;
    return;

}
int count_value(node* head, int input){
    int count = 0;

    node* cur = head;

    while(cur != NULL){
        if(cur->data == input){
            count++;
        }
        cur = cur->next;
    }
    return count;
}