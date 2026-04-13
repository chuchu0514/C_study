#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

Node *avail = NULL;
Node *get_node();
void ret_node(Node *node);
void cerase(Node **last);
void insert(Node ** last, int data);
void delete(Node ** last);
void print_linkedlist(Node * last);

int main(){
    FILE* fp = fopen("in.txt", "r");
    int num;
    fscanf(fp, "%d", &num);
    Node * last = NULL;
    int data1;
    for(int i = 0;i < num; i++){
        fscanf(fp, "%d", &data1);
        insert(&last, data1);
    }
    fclose(fp);

    printf("(1)Circular list: ");
    print_linkedlist(last);
    cerase(&last);
    printf("(2)cerase(): ");
    printf("%d ", avail->data);
    print_linkedlist(avail);
    Node * ptr1 = get_node();
    Node * ptr2 = get_node();
    Node * ptr3 = get_node();
    printf("(3)getNode(), getNode(), getNode(): ");
    printf("%d ", avail->data);
    print_linkedlist(avail);
    ret_node(ptr2);
    printf("(4)retNode(ptr2): ");
    printf("%d ", avail->data);
    print_linkedlist(avail);
}

// 노드 할당
Node *get_node() {
    Node *node;
    if (avail == NULL)
        node = (Node *)malloc(sizeof(Node));
    else {
        node = avail;
        avail = avail->next;
    }
    return node;
}

// 노드 반납
void ret_node(Node *node) {
    node->next = avail;
    avail = node;
}

// 원형 연결리스트 전체 삭제
void cerase(Node **last) {  
    if (*last == NULL) return;
    
    Node *temp = (*last)->next;
    (*last)->next = avail;
    avail = temp;
    *last = NULL;  
}
//삽입 
void insert(Node ** last, int data){

    Node* newnode = get_node();
    newnode -> data = data;

    if(*last == NULL){
        *last = newnode;
        newnode->next = newnode;//원형연결 자기자신
        return;
    }

    newnode->next = (*last)->next;//마지막 노드가 될 newnode의 next를 (*last)->next=head를 연결함으로써 원형연결
    (*last)->next = newnode;
    *last = newnode;
    return;
}

//원형연결리스트와 그냥 연결리스트인 avail을 동시 출력 가능하게 한 함수 
void print_linkedlist(Node * last){
    if(last == NULL){
        return;
    }

    Node* cur;
    cur = last->next;//avail의 경우 인자로 head를 주기 때문에 head->next가 cur이 되어버리므로 미리 head->data를 출력해놓아야함
    do{
        printf("%d ", cur->data);
        cur = cur->next;
    }while(cur != last->next && cur != NULL);//원형리스트의 경우 전자에, avail의 경우 후자의 조건에 걸림 
    printf("\n");
    return;
}

