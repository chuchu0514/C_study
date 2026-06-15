#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int data;
    struct node* next;
}node;
void insert(node** head, int data);
void dfs(node** ad, int* visited, int start, int parent);

int *visited;
int hascycle = 0;

int main(){

    FILE * fp  =fopen("input.txt", "r");
    int vertex, edge;
    int x, y;
    fscanf(fp, "%d %d", &vertex, &edge);
    node** ad = malloc(sizeof(node*)*vertex);
    visited = malloc(sizeof(int)*vertex);
    for(int i = 0; i < vertex; i++){
        ad[i] = NULL;
        visited[i] = 0;
    }
    for(int i = 0; i < edge; i++){
        fscanf(fp, "%d %d", &x, &y);
        insert(&ad[x], y);
        insert(&ad[y], x);
    }
    for(int i = 0; i < vertex; i++){
        if(visited[i] == 0){
            dfs(ad, visited, i, -1);
        }
    }

    if(hascycle){
        printf("cycle exists");
    }
    else{
        printf("no cycle");
    }
    fclose(fp);
    free(ad);
    return 0;
}

void insert(node** head, int data){
    node* newnode = malloc(sizeof(node));
    newnode->data = data;

    if(*head == NULL){
        newnode->next =NULL;
        *head = newnode;
        return;
    }

    newnode->next = *head;
    *head = newnode;
    return;
}
void dfs(node** ad, int* visited, int start, int parent){
    visited[start] = 1;
    printf("%d ", start);
    for(node* cur = ad[start]; cur!=NULL; cur = cur->next){
        if(visited[cur->data] == 0){
            dfs(ad, visited, cur->data, start);
        }
        else if(cur->data != parent){
            hascycle = 1;
        }
    }
}