#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void heapsort(int * arr, int n);

int main(){
    FILE *fp = fopen("input.txt", "r");
    int size;
    fscanf(fp, "%d", &size);
    int * arr = malloc(sizeof(int)*(size + 1));
    for(int i = 1; i <= size; i++){
        arr[i] = 0;
    }
    
    for(int i = 1; i <= size; i++){
        fscanf(fp, "%d", &arr[i]);
    }

    heapsort(arr, size);
    for(int i = 1; i <= size; i++){
        printf("%d ", arr[i]);
    }
    fclose(fp);
    free(arr);
    return 0;
}

void adjust(int * arr, int root, int n){
    int child = 2*root;
    int temp = arr[root];
    while(child <= n){
        if(child<n && arr[child] > arr[child+1]){
            child++;
        }
        if(temp <= arr[child]) break;

        arr[child/2] = arr[child];
        child *= 2;
    }
    arr[child/2] = temp;
}

void heapsort(int * arr, int n){
    for(int i = n/2; i>= 1; i--){
        adjust(arr, i, n);
    }
    for(int i = n - 1; i >= 1; i--){
        int temp = arr[1];
        arr[1] = arr[i+1];
        arr[i+1] = temp;
        adjust(arr, 1 ,i);
    }
}