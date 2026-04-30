//2023024050 추진성
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[50];
    int num;
    int data; // 벌점
} element;

element heap[MAX];
int heapSize = 0;

// min heap 삽입
void insertMinHeap(element item) {
    int i = ++heapSize;
    while (i > 1 && heap[i/2].data > item.data) {
        heap[i] = heap[i/2];
        i /= 2;
    }
    heap[i] = item;
}

// min heap 삭제 (루트 반환)
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

// max heap으로 변환 (heapify)
void makeMaxHeap() {
    int n = heapSize;
    for (int i = n/2; i >= 1; i--) {
        element temp = heap[i];
        int parent = i, child;
        while (2*parent <= n) {
            child = 2*parent;
            if (child < n && heap[child].data < heap[child+1].data)
                child++;
            if (temp.data >= heap[child].data) break;
            heap[parent] = heap[child];
            parent = child;
        }
        heap[parent] = temp;
    }
}

// postorder traversal (array 기반)
void postorder(element* list, int i, int N) {
    if (2*i <= N)
        postorder(list, 2*i, N);
    if (2*i+1 <= N)
        postorder(list, 2*i+1, N);
    printf("[%s,%d점]", list[i].name, list[i].data);
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

    // (1) level order - 배열 순서대로 출력
    printf("Min heap(level order):\n");
    for (int i = 1; i <= heapSize; i++) {
        printf("[%s,%d점]", heap[i].name, heap[i].data);
        if (i % 5 == 0) printf("\n");
    }
    printf("\n\n");

    // (2) 4명 삭제
    for (int i = 1; i <= 4; i++) {
        element deleted = deleteMinHeap();
        printf("Delete #%d [%s,%d번 ,%d점]\n", i, deleted.name, deleted.num, deleted.data);
    }

    // (3) max heap 변환 후 postorder
    makeMaxHeap();
    printf("After deleting(postorder):\n");
    postorder(heap, 1, heapSize);
    printf("\n");

    return 0;
}