//2023024050 추진성 
#define _CRT_SECURE_NO_WARNINGS
#define MAX_TERMS 100
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int row;
    int col;
    int value;
} term;

int main() {

    FILE *fp = fopen("m1.txt", "r");
    if (fp == NULL) {
        printf("파일 열기 실패\n");//예외처리 
        return 1;
    }

    int num_rows, num_cols, num_terms;//행의 개수, 열의 개수, value 개수 

    fscanf(fp, "%d %d %d", &num_rows, &num_cols, &num_terms);

    term *a = (term*)malloc(sizeof(term) * (num_terms + 1)); //sparse matrix의 행은 num_terms + 1 만큼 동적할당
    term *b = (term*)malloc(sizeof(term) * (num_terms + 1)); //전치 받을 구조체 ㄴ

    a[0].row = num_rows;
    a[0].col = num_cols;
    a[0].value = num_terms;

    for (int i = 1; i <= num_terms; i++) {
        fscanf(fp, "%d %d %d", &a[i].row, &a[i].col, &a[i].value); //sparse matrix 저장 
    }

    fclose(fp); //폴더 닫기 

    
    int row_terms[MAX_TERMS] = {0};// ++할거니까 모두 0으로 할당 
    int start_pos[MAX_TERMS];


    for (int i = 1; i <= num_terms; i++) { //각 열에 몇 개 있는지 세기 
        row_terms[a[i].col]++;
    }
    printf("\n");

    start_pos[0] = 1;
    printf("Initial Starting Position\n[0]1 ");
    for (int i = 1; i < num_cols; i++) {
        start_pos[i] = start_pos[i - 1] + row_terms[i - 1]; //시작 위치 계산과 initial starting position출력 
        printf("[%d]%d ", i, start_pos[i]);
    }

    printf("\n");
    printf("\n");

    for (int i = 1; i <= num_terms; i++) { //전치 
        int j = start_pos[a[i].col];

        b[j].row = a[i].col;
        b[j].col = a[i].row;
        b[j].value = a[i].value;

        start_pos[a[i].col]++;
    }

    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = num_terms; 

    printf("Final Starting Position\n");
    for (int i = 0; i < num_cols; i++) {
        printf("[%d]%d ", i, start_pos[i]); //Final starting position 출력 
    }

    printf("\n");
    printf("\n");
    printf("\n");

    printf("After Fast transpose\n");
    for (int i = 0; i <= num_terms; i++) {
        printf("<%d %d %d>\n", b[i].row, b[i].col, b[i].value); //결과출력 
    }



    free(a);// 메모리해제 
    free(b);

    return 0;
}

