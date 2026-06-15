//2023024050 추진성
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int size;
int digit(int number, int pos, int radix);
int radixSort(int* a, int* link, int n, int d, int radix);
int main(){
    FILE * fp = fopen("input3.txt", "r");
    fscanf(fp, "%d", &size);
    int* arr = malloc(sizeof(int)*(size+1));
    int* link = malloc(sizeof(int)*(size+1));

    for(int i = 1; i <= size; i++){
        fscanf(fp, "%d", &arr[i]);    // num 거칠 필요도 없이 바로
    }
    int first = radixSort(arr,link, size, 3, 10);
    int cur = first;
    while(cur) {
        printf("%d ", arr[cur]);
        cur = link[cur];
    }
}
int digit(int number, int pos, int radix){
    for(int i = 1; i < pos; i++){
        number /= radix;
    }
    return number % radix;
}

int radixSort(int* a, int* link, int n, int d, int radix){
    int front[10], rear[10];   
    int first, current, last;

    first = 1;
    for(int i = 1; i < n; i++) link[i] = i + 1;
    link[n] = 0;

    // 가장 낮은 자리(pos=1)부터 가장 높은 자리(pos=d)까지 반복
    for(int pos = 1; pos <= d; pos++){

        // 1) bin 비우기
        for(int b = 0; b < radix; b++){
            front[b] = 0;
            rear[b] = 0;
        }

        // 2) distribution: 체인을 따라가며 각 원소를 해당 bin에 매단다
        for(current = first; current != 0; current = link[current]){
            int b = digit(a[current], pos, radix);
            if(front[b] == 0){
                front[b] = current;          // bin이 비었으면 시작점
            } else {
                link[rear[b]] = current;     // 아니면 그 bin의 끝에 이어붙임
            }
            rear[b] = current;               // 끝을 갱신 (rear에 추가 = stable)
        }

        // 3) merging: bin 0번부터 9번까지 순서대로 다시 하나의 체인으로 연결
        first = 0;
        last = 0;
        for(int b = radix -1; b >= 0; b--){
            if(front[b] != 0){               // 비어있지 않은 bin만
                if(first == 0){
                    first = front[b];        // 첫 bin의 시작이 전체 시작
                } else {
                    link[last] = front[b];   // 이전 bin 끝과 이 bin 시작을 연결
                }
                last = rear[b];
            }
        }
        if(last != 0) link[last] = 0;        // 마지막 원소의 link는 0(끝)
    }

    return first;   // 가장 작은 원소의 인덱스
}