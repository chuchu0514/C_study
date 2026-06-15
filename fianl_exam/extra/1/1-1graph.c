#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
}node;

void insert(node** head, int data);
void BFS(node** link, int k, int visited[]);

int main(){
    FILE *fp = fopen("input.txt", "r");
    int vertex;
    int edge;
    int k;
    int x,y;
    fscanf(fp, "%d %d", &vertex, &edge);
    node** linkedlist = malloc(sizeof(node*) * vertex);
    for(int i = 0; i < vertex; i++){
        linkedlist[i] = NULL;
    }
    int* visited = malloc(sizeof(int)*vertex);
    for(int i = 0; i < vertex; i++){
        visited[i] = 0;
    }
    for(int i = 0; i < edge; i++){
        fscanf(fp, "%d %d", &x, &y);
        insert(&linkedlist[x], y);
        insert(&linkedlist[y], x);

    }
    fscanf(fp, "%d", &k);
    BFS(linkedlist, k, visited);
    fclose(fp);
    return 0;
}

void insert(node** head, int data){
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = data;

    // 맨 앞에 와야 하는 경우 (리스트 비었거나 head보다 작음)
    if(*head == NULL || (*head)->data > data){
        newnode->next = *head;
        *head = newnode;
        return;
    }
    // data보다 작은 노드들을 지나친 뒤 그 자리에 삽입
    node* cur = *head;
    while(cur->next != NULL && cur->next->data < data){
        cur = cur->next;
    }
    newnode->next = cur->next;
    cur->next = newnode;
}

void BFS(node** link, int k, int visited[]){
    int queue[100][2];
    int front = 0, rear = 0;
    visited[k] = 1;
    queue[rear][0] = k; queue[rear][1] = 0; rear++;
    while(front < rear){
        int v    = queue[front][0];
        int dist = queue[front][1];
        front++;
        if(dist == 2) continue;
        if(link[v] != NULL){
            for(node* cur = link[v]; cur; cur = cur->next){
                if(visited[cur->data] == 0){
                    visited[cur->data] = 1;
                    printf("%d ", cur->data);
                    queue[rear][0] = cur->data;
                    queue[rear][1] = dist + 1;
                    rear++;
                }
            }
        }
    }
}