//2023024050 추진성
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void insert_sort(int* arr, int start, int S);
void swap(int *a, int *b);
void quick_sort(int* arr, int left, int right);
int main(){
    int size;
    int num;
    FILE *fp = fopen("260518.txt", "r");
    fscanf(fp, "%d", &size);
    int * arr = (int*)malloc(sizeof(int)*size);
    for(int i = 0; i < size; i++){
        fscanf(fp, "%d", &num);
        arr[i] = num; //입력받음
    }
    int S;
    printf("Enter S: ");
    while(1){
        scanf("%d", &S);
        if(5 <= S && S <= 15) break;
    }
    printf("\n");
    printf("Insertion sort(segment size %d)\n", S);
    int q = size / S;
    for(int i = 0; i < q ; i++){
        insert_sort(arr, i * S, S);
    }
    if(size % S != 0){
        int remain = size % S;      
        insert_sort(arr, q*S, remain); //나머지
    }
    printf("\n\n");
    quick_sort(arr, 0, size - 1);
    printf("\nQuick sort\n");
    int count = 0;
    for(int i = 0; i < size; i++){
        printf("%4d", arr[i]);
        count++;
        if(count % 10 == 0) printf("\n");
    }

    fclose(fp);
    free(arr);
}

void insert_sort(int* arr, int start, int S){
    for(int i = start + 1; i < start + S; i++){
        int key = arr[i];
        int j = i - 1;

        while(j >= start && arr[j] > key){
            swap(&arr[j+1], &arr[j]);
            j--;
        }
        arr[j+1] = key;
    }

    for(int i = start; i < start + S; i++){
        printf("%3d ", arr[i]);
    }
    printf("\n");
}

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void quick_sort(int* arr, int left, int right){
    int pivot, i, j;

    if(left < right){
        i = left;
        j = right + 1;
        pivot = arr[left];
        if (pivot % 4 == 0){
            printf("Pivot: %d\n", pivot);
        }
        do{
            do i++; while(i <= right && arr[i] < pivot);  
            do j--; while(j >= left && arr[j] > pivot);   
            if(i < j) swap(&arr[i], &arr[j]);
        } while(i < j);

        swap(&arr[left], &arr[j]);
        quick_sort(arr, left, j - 1);
        quick_sort(arr, j+1, right);


    }
}
