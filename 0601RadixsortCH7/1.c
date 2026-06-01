//2023024050 추진성
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct element{
    char name[20];
    int class;
    int num;
}element;

int radixSort(element a[], int link[], int d, int r, int n);
int digit(element x, int j, int r);

int main(){
    FILE *fp = fopen("in1.txt", "r");
    int size;
    fscanf(fp, "%d", &size);
    element* e = (element*)malloc(sizeof(element)*(size+1));
    int* link = malloc(sizeof(int)*(size+1));

    for(int i = 1; i <= size; i++){
        fscanf(fp, "%s %d %d", e[i].name, &e[i].class, &e[i].num);
    }
    int first = radixSort(e, link, 3, 10, size);
    int cur = first;
    while(cur) {
        printf("%s %d %d\n", e[cur].name, e[cur].class, e[cur].num);
        cur = link[cur];
    }
    free(e);
    free(link);
    fclose(fp);
}

int digit(element x, int j, int r) {
    if (j == 1) return x.class;          //학년
    else if (j == 2) return (x.num / 10) % r; //번호 10의 자리
    else return x.num % r;               //번호 1의 자리
}
int radixSort(element e[], int link[], int d, int r, int n) {//d는key개수, r은bucket개수, n은 학생수 
    int* front = malloc(sizeof(int)*r);
    int* rear = malloc(sizeof(int)*r);
    int i, bin, current, first, last;

    first = 1;
    for (i = 1; i < n; i++) link[i] = i + 1;
    link[n] = 0;

    for (int j = d; j >= 1; j--) {

        for (i = 0; i < r; i++) front[i] = rear[i] = 0;

        current = first;
        while (current) {
            bin = digit(e[current], j, r); //j번째 자릿수
            if (front[bin] == 0) front[bin] = current;
            else link[rear[bin]] = current;
            rear[bin] = current;
            current = link[current];
        }

        // bucket에서 꺼내기
        first = last = 0;
        for (i = 0; i < r; i++) {
            if (front[i] != 0) {
                if (first == 0) first = front[i];
                else link[last] = front[i];
                last = rear[i];
            }
        }
        link[last] = 0;
    }
    free(front);
    free(rear);
    return first;
}