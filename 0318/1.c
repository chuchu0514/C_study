//2023024050 추진성 
#define _CRT_SECURE_NO_WARNINGS
#define MAX_TERMS 100
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int coef;
    int expon;
}polynomial;

polynomial terms[MAX_TERMS];
int avail = 0;
int starta, finisha;
int startb, finishb;
int startd, finishd;

void padd(int startA, int finishA, int startB, 
    int finishB, int *startD, int *finishD);//더하기 함수 
void attach(int coef, int expon);//구조체에 저장
int COMPARE(int a, int b);//expon 비교 
void print_poly(int start, int finish);//출력함수

int main(){
    
    FILE *fp;
    fp = fopen("a1.txt", "r");  //파일열기
    if (fp == NULL){
        printf("파일 열기 실패\n"); //오류처리 
        return 1;
    }

    int n;
    fscanf(fp, "%d", &n); //데이터 개수 받기 
    printf("(a1.txt)\n\n %d ",n);
    starta = avail;

    for (int i = 0; i < n; i++){
        fscanf(fp, "%d %d", &terms[avail].coef, &terms[avail].expon); //입력받기 trems에 저장 
        avail++;
    }

    finisha = avail - 1;
    print_poly(starta, finisha); //a1.txt출력

    fclose(fp);


    fp = fopen("b1.txt", "r");  //파일열기
    if (fp == NULL){
        printf("파일 열기 실패\n"); //오류처리 
        return 1;
    }

    fscanf(fp, "%d", &n); //데이터 개수 받기 
    printf("(b1.txt)\n\n %d ",n);
    startb = avail;

    for (int i = 0; i < n; i++){
        fscanf(fp, "%d %d", &terms[avail].coef, &terms[avail].expon); //입력받기 terms에 저장 
        avail++;
    }


    finishb = avail - 1;
    print_poly(startb, finishb); //b1.txt출력 

    fclose(fp);

    padd(starta, finisha, startb, finishb, &startd, &finishd);//padd함수 실행
    printf("수행 후:\n\n[결과 1]\n\n");

    int count = 0;
    for (int i = startd; i <= finishd; i++) {
        if (terms[i].coef != 0)
            count++; //0이 아닌 항의 개수 세기 
    }

    if (count == 0) {
        printf("0 0\n"); //만약 0이 아닌 항이 0개일 경우 0 0출력 
    } else {
        printf("%d ", count);//그렇지 않을 경우 count와 함께 출력 
        print_poly(startd, finishd);
    }
    printf("\n");





        fp = fopen("a2.txt", "r");  //파일열기
    if (fp == NULL){
        printf("파일 열기 실패\n"); //오류처리 
        return 1;
    }

    fscanf(fp, "%d", &n); //데이터 개수 받기 
    printf("(a2.txt)\n\n %d ",n);
    starta = avail;

    for (int i = 0; i < n; i++){
        fscanf(fp, "%d %d", &terms[avail].coef, &terms[avail].expon); //표준입력받기
        avail++;
    }

    finisha = avail - 1;
    print_poly(starta, finisha); //a2.txt출력 

    fclose(fp);


    fp = fopen("b2.txt", "r");  //파일열기
    if (fp == NULL){
        printf("파일 열기 실패\n"); //오류처리 
        return 1;
    }

    fscanf(fp, "%d", &n); //데이터 개수 받기 
    printf("(b2.txt)\n\n %d ",n);
    startb = avail;

    for (int i = 0; i < n; i++){
        fscanf(fp, "%d %d", &terms[avail].coef, &terms[avail].expon); //표준입력받기 
        avail++;
    }


    finishb = avail - 1;
    print_poly(startb, finishb); //b2.txt출력 

    fclose(fp);

    padd(starta, finisha, startb, finishb, &startd, &finishd);

    printf("수행 후:\n\n[결과 2]\n\n");

    int count2 = 0;
    for (int i = startd; i <= finishd; i++) {
        if (terms[i].coef != 0)
            count2++;
    }

    if (count2 == 0) {
        printf("0 0\n");
    } else {
        printf("%d ", count2);
        print_poly(startd, finishd);
    }
    return 0;
}

void padd(int startA, int finishA, int startB, 
    int finishB, int *startD, int *finishD){

    int coefficient;
    *startD = avail; 

    while (startA <= finishA && startB<= finishB)

    switch(COMPARE(terms[startA].expon, //A다항식과 B다항식의 지수비교 
    terms[startB].expon)){

    case -1: /* a expon < b expon */
        attach(terms[startB].coef, 
        terms[startB].expon); 
        startB++;
        break;

    case 0: /* equal exponents */
        coefficient = terms[startA].coef + 
        terms[startB].coef;
        if(coefficient)
        attach(coefficient, terms[startA].expon);
        startA++;
        startB++;
        break;

    case 1: /* a expon > b expon */
        attach(terms[startA].coef, 
        terms[startA].expon);
        startA++;
    }

    /* add in remaining terms of A(x) */
    for( ; startA <= finishA; startA++)
    attach(terms[startA].coef, terms[startA].expon);
    /* add in remaining terms of B(x) */
    for( ; startB <= finishB; startB++) 
    attach(terms[startB].coef, terms[startB].expon);


    *finishD = avail -1; 
}

void attach(int coef, int expon){
    terms[avail].coef = coef;
    terms[avail].expon = expon;
    avail++;
}

int COMPARE(int a, int b){
    if (a > b) return 1;
    else if (a == b) return 0;
    else return -1;
}

void print_poly(int start, int finish){
    for (int i = start; i <= finish; i++){
        if (terms[i].coef != 0){
        printf("%d %d ", terms[i].coef, terms[i].expon);
        }
    }
    printf("\n\n");
}
