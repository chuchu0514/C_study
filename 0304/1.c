//2023024050 추진성

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>


struct Accessor{
    char id[100];
    int minute;
};

int main(){

   

    FILE *fp;
    fp = fopen("in.txt", "r");  //파일열기
    if (fp == NULL){
        printf("파일 열기 실패\n"); //오류처리 
        return 1;
    }

    int n;
    fscanf(fp, "%d", &n); //데이터 개수 받기 

    struct Accessor *arr;
    
    arr = (struct Accessor *)malloc(n * sizeof(struct Accessor)); //동적할당 

    for (int i = 0; i < n; i++){
        fscanf(fp, "%s %d", arr[i].id, &arr[i].minute); //구조체 배열에 저장
    }
    fclose(fp); //파일 닫기
    
    int time;
    printf("기준 시간을 입력하세요: "); //기준 시간 표준입력 
    scanf("%d", &time);
    printf("\n");

    printf("Enter usage time: %d\n", time);
    printf("%d 이상 사용한 사용자\n",time); //사용자 정보 표준출력
    for(int i= 0; i < n; i++){
        if (arr[i].minute >= time){
            printf("%s %d\n", arr[i].id, arr[i].minute);
        }
    }

    fp = fopen("out.txt", "w"); //out txt오픈
    if (fp == NULL){
        printf("파일 열기 실패\n");//오류 처리 
        return 1;
    }

    for (int i = 0; i < n; i++){
        if (arr[i].minute <= time){
            fprintf(fp, "%s %d\n", arr[i].id, arr[i].minute);//out txt에 출력 
        }
    }

    fclose(fp);
    
    free(arr); 

    return 0;

}

