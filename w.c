#include <stdio.h>
#include <stdlib.h>
#define MAX_V 100 //최대 정점 수를 임의로 정함
void findFriend(int** arr, int* cnt, int n, int start, int N, char names[][4]) {
    //arr:인접리스트, cnt[i]:정점 i의 이웃 수, n:vertex의 총 수 , start:시작 정점, N: 구하고자 하는 단계, names: 이름 A B C저장용도
    int visited[MAX_V] = {0};//정점을 방문했는지 저장하는 역할
    int distance[MAX_V];//start와 정점 i간의 거리를 저장
    int queue[MAX_V];//BFS구현을 위한 큐 
    int front = 0, rear = -1;

    for (int i = 0; i < n; i++) distance[i] = -1;//distance배열 초기화
    visited[start] = 1; //start정점 방문처리
    distance[start] = 0; //자기자신과의 거리 0
    queue[++rear] = start; //큐에 start 추가
    
    while(front <= rear){//큐가 비어있지 않다면
        int v = queue[front++]; //큐에서 deque 
        for(int i = 0; i < cnt[v]; i++){//정점 v의 이웃을 다 돌기 위함
            if(!visited[arr[v][i]]){//해당 정점을 방문하지 않았다면
                visited[arr[v][i]] = 1;//방문처리
                queue[++rear] = arr[v][i];//큐에 
                distance[arr[v][i]] = distance[v] + 1; //부모거리 +1
            }
        }
    }

for(int i = 0; i < n; i++){
        if(distance[i] == N){
            printf("%s ", names[i]);  // 이름출력
        }
    }
}