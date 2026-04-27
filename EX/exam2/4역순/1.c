//16분
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int count_arr(int arr[], int rep, int size, int count, int k);
void reverse(int arr[], int rep, int size, int k, int size2);

int main(){
    int arr[] = {3, 7, 1, 9, 2, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    int k;
    int count;
    printf("input k: ");
    scanf("%d", &k);
    count = count_arr(arr, 0, size, 0, k);
    printf("count: %d\n", count);
    printf("reverse: ");
    reverse(arr, 0, size, k, size);
    
}

int count_arr(int arr[], int rep, int size, int count, int k){
    if(rep == size){
        return count;
    }
    if(arr[rep] > k){
        count++;
    }
    rep++;
    return count_arr(arr, rep, size, count, k);

}
void reverse(int arr[], int rep, int size, int k, int size2){
    if(rep == size){
        return;
    }
    if(arr[size2-1] > k){
        printf("%d ", arr[size2-1]);
    }
    rep++;
    reverse(arr, rep, size, k, size2-1);
}