//2023024050 추진성 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


void free3DArray(int*** arr, int X, int Y, int Z);
void print3DArray(int*** arr, int X, int Y, int Z);

int main(){

    int X, Y, Z;
    printf("Enter: X, Y, Z: ");
    scanf("%d %d %d", &X, &Y, &Z);
    printf("\n");
    int *** arr;

    arr = (int***)malloc(sizeof(int**) * X);

    for(int i = 0; i < X; i++){
        arr[i] = (int**)malloc(sizeof(int*) * Y);

        for(int j = 0; j < Y; j++){
            arr[i][j] = (int*)malloc(sizeof(int) * Z);
        }
    }


    for(int i = 0; i < X; i++){
        for(int j = 0; j < Y; j++){
            for(int k = 0; k < Z; k++){
                arr[i][j][k] = i + j + k;
            }
        }
    }

    print3DArray(arr, X, Y, Z); 
    free3DArray(arr, X, Y, Z);

    return 0;
}

void print3DArray(int *** arr, int X, int Y, int Z){
    
    for(int i = 0; i < X; i++){
        for(int j = 0; j < Y; j++){
            for(int k = 0; k < Z; k++){
                printf("A[%d][%d][%d] = %d ", i, j, k, arr[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void free3DArray(int*** arr, int X, int Y, int Z){

    for(int i = 0; i < X; i++){
        for(int j = 0; j < Y; j++){
            printf("free arr[%d][%d]\n", i, j);
            free(arr[i][j]);
        }
        printf("free arr[%d]\n", i);
        free(arr[i]);
    }    

    free(arr);
    printf("free arr");
}
