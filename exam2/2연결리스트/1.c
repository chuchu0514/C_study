//47분
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
}node;

void insert(node** head, int data);
void print_node(node* head);
void remove_dup(node** head, int size);
void func(node** head);

int main(){
    FILE *fp = fopen("a1.txt", "r");
    int size, num;
    node* head = NULL;
    fscanf(fp, "%d", &size);
    for(int i = 0; i < size; i++){
        fscanf(fp, "%d", &num);
        insert(&head, num);
    }
    fclose(fp);
    printf("List: ");
    print_node(head);
    printf("Removed: ");
    remove_dup(&head, size);
    print_node(head);
    printf("Result: ");
    func(&head);
    print_node(head);
    
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

    node* cur= *head;
    while(cur->next != NULL){
        cur = cur->next;
    }
    cur->next = newnode;
    return;
}
void print_node(node* head){
    node*cur = head;
    while(cur != NULL){
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
    return;
}
void remove_dup(node** head, int size){

    node* cur1 = *head;
    int data;
    while(cur1 != NULL){
        data = cur1->data;
        node * prev = NULL;
        node* cur2 = cur1->next;
        while(cur2!= NULL){
            if(data == cur2->data){
                if(prev == NULL){
                    node* temp = cur2;
                    cur1->next = cur2->next;
                    cur2 = cur2->next;
                    free(temp);
                }
                else{
                    node* temp = cur2;
                    prev->next = cur2->next;
                    cur2 = cur2->next;
                    free(temp);
                }
            }
            else{
                prev = cur2;
                cur2 = cur2->next;
            }
        }
        cur1 = cur1->next;
    }
}
void func(node** head){
    int indexmin = 0;
    int count = 0;
    node* cur = *head;
    int min = cur->data;

    while(cur->next != NULL){
        
        if(min > cur->next->data){
            min = cur->next->data;
            indexmin = count + 1;
        }
        count++;
        cur = cur->next;
    }
    if (indexmin == 0) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = min - 10;
    newnode->next = *head;
    *head = newnode;
    node* newnode2 = (node*)malloc(sizeof(node));
    newnode2->data = min + 10;
    newnode2->next = newnode->next->next;
    newnode->next->next = newnode2;
    }
    else{
        cur = *head;
        for(int i = 0; i < indexmin - 1; i++){
            cur = cur->next;
        }
        node* newnode = (node*)malloc(sizeof(node));
        newnode-> data = cur->next->data - 10;
        newnode-> next = cur->next;
        cur->next = newnode;
        node* newnode2 = (node*)malloc(sizeof(node));
        newnode2-> data = newnode->next->data + 10;
        newnode2-> next = newnode->next->next;
        newnode->next->next = newnode2; 
    }
    return;
}