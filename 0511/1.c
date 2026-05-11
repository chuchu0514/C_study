//2023024050 추진성
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void DFS(int** arr, int* visited, int input, int size);
void BFS(int** arr, int* visited, int input, int size);
void DFS_Sp(int** arr, int* visited, int input, int parent, int size);
void BFS_Sp(int** arr, int* visited, int input, int size);


int main(){
    FILE *fp = fopen("260511.txt", "r");
    int size;
    int num;
    fscanf(fp, "%d", &size);
    int * visited = (int*)malloc(sizeof(int)*size);//방문 배열
    for(int i = 0; i < size; i++){
        visited[i] = 0;
    }
    int** arr = (int**)malloc(sizeof(int*)*size); //인접 행렬
    for(int i =0; i < size; i++){
        arr[i] = malloc(sizeof(int)*size);
    }

    for(int i = 0; i < size; i++){ //인접 행렬 할당 
        for(int j = 0; j < size; j++){
            fscanf(fp, "%d", &num);
            arr[i][j] = num;
        }
    }
    int input;
    printf("(1) DFS, BFS:\n");
    printf("DFS: \n");
    while(1){
        for(int i = 0; i < size; i++){
        visited[i] = 0;
        }
        printf("Starting number: ");
        scanf("%d", &input);
        if(input < 0 || input >= size) break;
        DFS(arr, visited, input, size);
        printf("\n");
    }
    printf("\n");

    printf("BFS: \n");
    while(1){
        for(int i = 0; i < size; i++){
        visited[i] = 0;
        }        
        printf("Starting number: ");
        scanf("%d", &input);
        if(input < 0 || input >= size) break;
        BFS(arr, visited, input, size);
        printf("\n");
    }
    printf("\n");

    printf("(2) Spanning Tree: \n");
    while(1){
        printf("Starting number: ");
        scanf("%d", &input);
        if(input < 0 || input >= size) break;
        for(int i = 0; i < size; i++){
        visited[i] = 0;
        }
        printf("DFS Spanning Tree:\n");
        DFS_Sp(arr, visited, input, -1, size);
        printf("\n");

        for(int i = 0; i < size; i++){
        visited[i] = 0;
        }              
        printf("BFS Spanning Tree:\n");

        BFS_Sp(arr, visited, input, size);

        printf("\n\n");

    }


    fclose(fp);
    free(visited);
    for(int i = 0; i < size; i++){
        free(arr[i]);
    }
    free(arr);
}

void DFS(int** arr, int* visited, int input, int size){
    visited[input] = 1; //해당지점 방문
    printf(" %d ", input);

    for(int i = 0; i < size; i++){
        if(arr[input][i] == 1 && !visited[i]){//인접행렬에서 서로 연결되어있고, 방문이 안 되어있다면
            DFS(arr, visited, i, size);
        }
    }

}

void BFS(int** arr, int* visited, int input, int size){
    int* queue = malloc(sizeof(int)*size);
    int front = 0, rear = -1;
    visited[input] = 1;

    printf(" %d ", input);
    queue[++rear] = input;//큐의 첫 인덱스에 input입력

    while(front <= rear){//큐가 비어있지 않을 때까지
        int v = queue[front++];//큐에서 제일 앞 원소 꺼내고 

        for(int i = 0; i < size; i++){
            if(arr[v][i] == 1 && !visited[i]){
                visited[i] = 1;
                printf(" %d ", i);
                queue[++rear] = i;
            }

        }
    }
    free(queue);


}

void DFS_Sp(int** arr, int* visited, int input, int parent, int size){
    visited[input] = 1;

    if(parent != -1)//첫 input은 출력x                   
        printf("(%d, %d)", parent, input);  
    for(int i = 0; i < size; i++){
        if(arr[input][i] == 1 && !visited[i]){
            DFS_Sp(arr, visited, i, input, size);
        }
    }
}

void BFS_Sp(int** arr, int* visited, int input, int size){
    int* queue = malloc(sizeof(int)*size);
    int front = 0, rear = -1;
    visited[input] = 1;
    queue[++rear] = input;

    while(front <= rear){
        int v = queue[front++];
        for(int i = 0; i < size; i++){
            if(arr[v][i] == 1 && !visited[i]){
                visited[i] = 1;
                printf("(%d, %d)", v, i);
                queue[++rear] = i;
            }

        }
    }
    free(queue);

}