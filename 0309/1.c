//2023024050 추진성 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100000
#define MAX 100000000 //MAX값은 수정가능

int iter_binsearch(int list[], int key, int left, int right); //함수 정의 
int recur_binsearch(int list[], int key, int left, int right);

void main() {
clock_t start, finish;
long repetition = 0; //반복횟수
double elapsed; //경과시간 
int arr[SIZE];

for (int i = 0; i < SIZE; i++){
    arr[i] = i;
}; //배열 할당 

start = clock();
repetition = 0;

do {
iter_binsearch(arr, -10, 0, SIZE - 1);  //iterative 이진탐색 
repetition++;
} while (repetition <= MAX);

finish = clock();
elapsed = ((double)finish - (double)start)/ CLOCKS_PER_SEC;
printf("Iterative binary search: %f \n", elapsed);
 
start = clock();
repetition = 0;

do {
recur_binsearch(arr, -10, 0, SIZE - 1);  //recursive 이진탐색 
repetition++;
} while (repetition <= MAX);

finish = clock();
elapsed = ((double)finish - (double)start)/ CLOCKS_PER_SEC;
printf("recursive binary search: %f \n", elapsed);
 

}

int iter_binsearch(int list[], int key, int left, int right){
    int middle;

    while (left <= right) {
        middle = (left + right) / 2;

        if (list[middle] == key)
            return middle;

        else if (list[middle] < key)
            left = middle + 1;

        else
            right = middle - 1;
    }

    return -1; 
}

int recur_binsearch(int list[], int key, int left, int right)
{
    int middle;

    if (left > right)
        return -1;

    middle = (left + right) / 2;

    if (list[middle] == key)
        return middle;

    else if (list[middle] < key)
        return recur_binsearch(list, key, middle + 1, right);

    else
        return recur_binsearch(list, key, left, middle - 1);
}