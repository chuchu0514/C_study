//2023024050 추진성
#define _CRT_SECURE_NO_WARNINGS
#define SWAP(a, b, t) ((t)=(a), (a)=(b), (b)=(t)) //swap 정의 
#include <stdlib.h>
#include <stdio.h>

typedef struct student{
    char name[20];
    int priority;
    int order;
}student;

void adjust(student st[], int root, int n);
int compare(student p1, student p2);
void heapSort(student st[], int n);
void printheap(student st[], int size);

int main(){
    FILE *fp = fopen("in.txt", "r");
    int size;
    fscanf(fp, "%d", &size);
    student* st = malloc(sizeof(student) * (size + 1)); 
    for(int i = 1; i <= size; i++){                       
        fscanf(fp, "%s %d", st[i].name, &st[i].priority);
        st[i].order = i;
    }
    printf("[after heap sort]\n");
    heapSort(st, size);
    printheap(st, size);

    fclose(fp);
    free(st);
}

int compare(student p1, student p2) {
    if (p1.priority != p2.priority)
        return p2.priority - p1.priority;  //p1이 크면 음수 p2가 크면 양수
    else
        return p1.order - p2.order;        //p1이 크면 음수 p2가 크면 양수
}

void adjust(student st[], int root, int n) {
    int child;
    student temp;
    
    temp = st[root];
    child = 2 * root;  // 왼쪽 자식
    
    while (child <= n) {
        if ((child < n) && compare(st[child], st[child + 1]) < 0)//p1이 크다면 더 작은 p2선택 min heap으로 구현함
            child++;
        if (compare(temp, st[child]) > 0)//minheap이니까 p2가 더크면 즉 자식이 더 크다면 멈춤 
            break;
        else {
            st[child/2] = st[child];
            child *= 2;
        }
    }
    st[child/2] = temp;
}

void heapSort(student st[], int n) {
    student temp;
    //heap 만들기
    for (int i = n/2; i > 0; i--)
        adjust(st, i, n);
    
    //정렬하기
    for (int i = n-1; i > 0; i--) {
        SWAP(st[1], st[i+1], temp);
        adjust(st, 1, i);
    }
}

void printheap(student st[], int size){
    printf("name:   priority  order\n");
    for(int i = 1; i <= size; i++){
        printf("%5s: %7d %6d\n", st[i].name, st[i].priority, st[i].order);
    }
}