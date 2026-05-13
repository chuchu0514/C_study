#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
    int x, y;
    int cost;
} edge;

int *parent;

int find(int i) {
    if (parent[i] < 0) return i; //-1이면 본인이 루트 
    return find(parent[i]);
}

void myunion(int a, int b) { 
    parent[b] = a; 
}

int main() {
    FILE *fp = fopen("260513.txt", "r");
    int n;
    fscanf(fp, "%d", &n);
    int **matrix = (int **)malloc(sizeof(int *)*n);//동적할당
    for (int i = 0; i < n; i++)
        matrix[i] = (int *)malloc(sizeof(int)*n);

    parent = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)//부모배열 초기화 
        parent[i] = -1;    

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fscanf(fp, "%d", &matrix[i][j]); //값 할당 

    int ecount = 0; //edges의 인덱스 
    edge *edges = (edge*)malloc(sizeof(edge) * n * n);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)//중복제거
            if (matrix[i][j] > 0) { //0 아닌 것만 저장 
                edges[ecount].x = i;
                edges[ecount].y = j;
                edges[ecount].cost = matrix[i][j];
                ecount++;
            }

    for (int i = 0; i < ecount - 1; i++)//코스트 정렬 
        for (int j = i + 1; j < ecount; j++)
            if (edges[i].cost > edges[j].cost) {
                edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }


    int count = 0;

    for (int i = 0; i < ecount; i++) {//Kruskal
        if (count == n - 1)break; //간선 수가 n-1개면 mst완성 
        int rx = find(edges[i].x);
        int ry = find(edges[i].y);
        if (rx != ry) {
            printf("Add (%d, %d): %d\n", edges[i].x, edges[i].y, edges[i].cost);
            myunion(rx, ry);
            count++;
        } else {//사이클
            printf("Not add (%d, %d): %d\n", edges[i].x, edges[i].y, edges[i].cost);
        }
    }

    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
    free(edges);
    fclose(fp);
    return 0;
}