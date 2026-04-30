//2023024050 추진성 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

typedef struct {
    char name[50];
    int num;
    int data; 
} element;

element heap[MAX_SIZE];
int heapSize = 0;


void insertMinHeap(element item) {
    int i = ++heapSize;
    while (i > 1 && heap[i/2].data > item.data) {
        heap[i] = heap[i/2];
        i /= 2;
    }
    heap[i] = item;
}

element deleteMinHeap() {
    element min = heap[1];
    element last = heap[heapSize--];
    int i = 1, child;

    while (2*i <= heapSize) {
        child = 2*i;
        if (child < heapSize && heap[child].data > heap[child+1].data)
            child++;
        if (last.data <= heap[child].data) break;
        heap[i] = heap[child];
        i = child;
    }
    heap[i] = last;
    return min;
}

int main() {
    FILE* fp = fopen("in.txt", "r");
    int n;
    fscanf(fp, "%d", &n);
    for (int i = 0; i < n; i++) {
        element e;
        fscanf(fp, "%s %d %d", e.name, &e.num, &e.data);
        insertMinHeap(e);
    }
    fclose(fp);

    //배열출력
    printf("Min heap(level order):\n");
    for (int i = 1; i <= heapSize; i++) {
        printf("[%s, %d점]", heap[i].name, heap[i].data);
        if (i % 5 == 0) printf("\n");
    }
    printf("\n\n");

    //4명삭제
    for (int i = 1; i <= 4; i++) {
        element deleted = deleteMinHeap();
        printf("Delete #%d [%s,%d번, %d점]\n", i, deleted.name, deleted.num, deleted.data);
    }

    return 0;
}