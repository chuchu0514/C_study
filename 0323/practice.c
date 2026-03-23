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

void fastTranspose(term *a, term *b) {
    int row_terms[MAX_TERMS] = {0};
    int start_pos[MAX_TERMS];
    int i, j;

    int num_cols = a[0].col;
    int num_terms = a[0].value;

    // 1️⃣ 각 열에 몇 개 있는지 세기
    for (i = 1; i <= num_terms; i++) {
        row_terms[a[i].col]++;
    }

    // 2️⃣ 시작 위치 계산
    start_pos[0] = 1;
    for (i = 1; i < num_cols; i++) {
        start_pos[i] = start_pos[i - 1] + row_terms[i - 1];
    }

    // 3️⃣ 전치
    for (i = 1; i <= num_terms; i++) {
        j = start_pos[a[i].col];

        b[j].row = a[i].col;
        b[j].col = a[i].row;
        b[j].value = a[i].value;

        start_pos[a[i].col]++;
    }

    // metadata
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = num_terms;
}

int main() {

    FILE *fp = fopen("m1.txt", "r");
    if (fp == NULL) {
        printf("파일 열기 실패\n");
        return 1;
    }

    int num_rows, num_cols, num_terms;

    // 첫 줄: 행, 열, 항 개수
    fscanf(fp, "%d %d %d", &num_rows, &num_cols, &num_terms);

    term *a = (term*)malloc(sizeof(term) * (num_terms + 1));
    term *b = (term*)malloc(sizeof(term) * (num_terms + 1));

    a[0].row = num_rows;
    a[0].col = num_cols;
    a[0].value = num_terms;

    for (int i = 1; i <= num_terms; i++) {
        fscanf(fp, "%d %d %d",
               &a[i].row,
               &a[i].col,
               &a[i].value);
    }

    fclose(fp);

    // 전치 수행
    fastTranspose(a, b);

    // 결과 출력
    printf("Transpose Result:\n");
    for (int i = 0; i <= num_terms; i++) {
        printf("%d %d %d\n",
               b[i].row,
               b[i].col,
               b[i].value);
    }

    // 메모리 해제
    free(a);
    free(b);

    return 0;
}