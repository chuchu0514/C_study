//2023024050 추진성 
#define _CRT_SECURE_NO_WARNINGS
#define STUDENT 5
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student{
    int class;
    char name[20];
    int grade;
}student;

void mergeSort(student* list, int n);
int rmergeSort(student* list, student* extra, int left, int right);
int listMerge(student* list, student* extra, int start1, int start2, int end);
void merge(student* list, student* extra, int i, int m, int n);
void mergePass(student* list, student* extra, int n, int s);
void printlist(student* list, int size);

int main(){
    FILE * fp = fopen("merge.txt", "r");
    int size;
    fscanf(fp, "%d", &size);
    student * st = (student*)malloc(sizeof(student) * (size+1)); //동적할당
    student* extra = (student*)malloc(sizeof(student) * (size+1));
    for(int i = 1; i < size + 1; i++){
        char temp[20];
        fscanf(fp, "%s %d", temp, &st[i].grade);
        st[i].class = temp[0] - '0';  //파싱
        strcpy(st[i].name, temp);
    }
    printf("반별 정렬 (Recursive merge sort): \n");
    for(int i = 0; i < 8; i++){
        rmergeSort(st, extra, i*STUDENT + 1, (i+1)*STUDENT);
    }
    printlist(st, size);

    printf("\n전체 정렬 (Iterative merge sort): \n");
    mergeSort(st, size);

    fclose(fp);
    free(st);
    free(extra);
}

void printlist(student* list, int size){
    int count = 0;
    for(int i = 1; i < size + 1; i++){
        printf("[%-6s %2d]",list[i].name, list[i].grade);
        count++;
        if(count % 5 == 0) printf("\n");
    }
}

void mergePass(student* list, student* extra, int n, int s){// n은 전체 크기, s는 segment 크기
    int i = 1;
    
    while(i <= n - 2*s + 1){         // 두 segment가 온전히 있는 경우
        merge(list, extra, i, i+s-1, i+2*s-1);
        i += 2*s;
    }
    
    if(i + s - 1 < n){               // 두 번째 segment가 불완전한 경우
        merge(list, extra, i, i+s-1, n);
    } 
    else {                          // 두 번째 segment 자체가 없는 경우 s=80..
        for(int j = i; j <= n; j++){
            extra[j] = list[j];       // 그냥 복사
        }
    }
}
void mergeSort(student* list, int n) {
    student* extra = (student*)malloc(sizeof(student) * (n + 1));
    
    int s = STUDENT; // 5
    while (s < n) {
        mergePass(list, extra, n, s);
        s *= 2; 
        printlist(extra, n);  // extra 출력
        puts("====================================================");
        
        mergePass(extra, list, n, s);
        s *= 2; 
        printlist(list, n);   // list 출력
        puts("====================================================");
    }
    free(extra);
}

int rmergeSort(student* list, student* extra, int left, int right) {
    if (left >= right)
    return left; //기저조건

    int mid = (left + right) / 2;

    return listMerge(list, extra,
        rmergeSort(list, extra, left, mid),     // start1
        rmergeSort(list, extra, mid+1, right),  // start2
        right);                                  // end
}

int listMerge(student* list, student* extra, int start1, int start2, int end) {
    merge(list, extra, start1, start2-1, end);  
    for(int i = start1; i <= end; i++){
        list[i] = extra[i];
    }
    return start1;//rmerge가 int형이니까 형태 맞춤
}

void merge(student* list, student* extra, int i, int m, int n) {//i m n -> segment1 시작 인덱스, 끝 인덱스, segment2 끝 인덱스 
    int j = m + 1;// 두 번째 segment 시작 인덱스
    int k = i;      //extra 위치

    while (i <= m && j <= n) {
        if (list[i].grade >= list[j].grade)  
            extra[k++] = list[i++];
        else
            extra[k++] = list[j++];
    }
    // 남은 거 복사
    while (i <= m) extra[k++] = list[i++];
    while (j <= n) extra[k++] = list[j++];
}