//2023024050 추진성 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


int count_num(int arr[], int arr2[], int num, int rep, int count, int size) {//조건에 따른 개수를 세는 함수 

    if (rep == size)
        return count;//종료조건

    if (arr[rep] > num) {
        arr2[count] = arr[rep];//입력받은 num보다 큰 수는 arr2라는 배열에 따로 저장과 동시에 count ++
        count++;
    }


    rep++;
    return count_num(arr, arr2, num, rep, count, size);//재귀함수

}

void reverse_print(int arr2[], int count) {//역순으로 출력하는 함수
    if (count > 0) {
        printf("%d ", arr2[count - 1]);
        count--;
        reverse_print(arr2, count);//재귀함수
    }

}

void main() {

    int arr[] = { 25, 31, 17, 50, 91, 15, 33, 100, 77, 56 };
    int size = sizeof(arr) / sizeof(arr[0]);
    int* arr2 = malloc(sizeof(int) * size); //따로 수를 저장할 배열 동적할당
    int num;
    printf("Enter number: ");
    scanf("%d", &num);
    int count = count_num(arr, arr2, num, 0, 0, size);
    printf("%d 보다 큰 정수의 개수: %d \n", num, count);
    printf("%d 보다 큰 정수 역수 출력 : ", num);
    reverse_print(arr2, count);


}

