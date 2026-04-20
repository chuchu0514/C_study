//2023024050 추진성
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{

    int coef; //계수
    int expo; //지수
    struct Node * next;
}Node;

Node* readFile(char* filename);
void printnode(Node* head);
Node* padd(Node* a, Node* b);
void erase(Node* head);
void attach(int coef, int expo, Node** rear);
int COMPARE(int a, int b);

int main(){
    Node* a1head = readFile("a1.txt");
    Node* b1head = readFile("b1.txt");
    printf("[결과 1]\n");
    printf("A(x): ");
    printnode(a1head); //A(x)출력
    printf("B(x): ");
    printnode(b1head); //B(x)출력
    Node* c1head = padd(a1head,b1head);
    printf("A(x)+B(x): ");
    if(c1head == NULL){ //NULL이라면 0 출력 
        printf("0\n");
    }
    else{
        printnode(c1head); //그게 아니라면 A+B출력 
    }
    erase(a1head);
    erase(b1head);
    erase(c1head);

    Node* a2head = readFile("a2.txt");
    Node* b2head = readFile("b2.txt");
    printf("[결과 2]\n");
    printf("A(x): ");
    printnode(a2head);
    printf("B(x): ");
    printnode(b2head);
    Node* c2head = padd(a2head,b2head);
    printf("A(x)+B(x): ");
    if(c2head == NULL){
        printf("0\n");
    }
    else{
        printnode(c2head);

    }

    erase(a2head);
    erase(b2head);
    erase(c2head);
    return 0;
}


void printnode(Node* head){

    Node* cur;
    cur = head;
    while(cur != NULL){
        printf("<%d, %d>",cur->coef, cur->expo);
        cur = cur -> next;
    }
    printf("\n");
    return;
}
Node* readFile(char* filename) {
    Node* head = NULL;   
    Node* tail = NULL;   //연결리스트의 끝

    FILE* fp = fopen(filename, "r");
    int n;
    fscanf(fp, "%d", &n);  // 항 개수

    for (int i = 0; i < n; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        fscanf(fp, "%d %d", &newNode->coef, &newNode->expo);
        newNode->next = NULL;

        if (head == NULL) head = tail = newNode;  // 첫 노드
        else { tail->next = newNode; tail = newNode; }  //끝노드 갱신 
    }
    fclose(fp);
    return head;
}
void attach(int coef, int expo, Node** rear){ //끝노드 갱신 
    Node * temp = (Node*)malloc(sizeof(Node));
    temp->next = NULL;
    temp->coef = coef;
    temp->expo = expo;
    (*rear)->next = temp;
    *rear = temp;
}

int COMPARE(int a, int b){//a b 지수비교함수 
    if (a > b) return 1;
    else if (a == b) return 0;
    else return -1;
}

Node* padd(Node* a, Node* b){
    Node *c;
    Node *rear = (Node*)malloc(sizeof(Node));
    rear->next = NULL;
    c = rear; //처음 dummy인 head를 가르킴 

    int sum; //a b지수 같을 때..

    while(a && b){
        switch (COMPARE(a->expo,b->expo)){ 
        case -1: //a의 지수 < b의 지수 
            attach(b->coef,b->expo,&rear);
            b = b->next;
            break;

        case 0: //a의 지수 = b의 지수 
            sum = a->coef + b->coef;
            if(sum){
                attach(sum, a->expo, &rear);
            }
            a = a->next;
            b = b->next;
            break;

        case 1: //a의 지수 > b의 지수 
            attach(a->coef, a->expo, &rear);
            a = a->next;
            break;
        }
    }
    //둘 중 남은 것 다 rear에다 attach하기 
    for(; a; a = a->next)
        attach(a->coef, a->expo, &rear);

    for(; b; b = b->next)
        attach(b->coef, b->expo, &rear);


    Node* temp = c; 
    c = c->next;
    free(temp); //dummy head날려버리기 

    return c;
}

void erase(Node* head){ //free겸 제거함수 
    Node * temp;
    while(head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("Erase\n");
}
