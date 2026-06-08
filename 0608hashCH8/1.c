//2023024050 추진성
#define _CRT_SECURE_NO_WARNINGS
#define B 41
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element{
    char name[20];
    int grade;
    int collision;
}element;

int h(char* key);
int insert(element ht[], element e);
void print_e(element* ht);
int search(element ht[], char * name);

int main(){
    FILE *fp = fopen("hashing.txt", "r");
    int size;
    fscanf(fp, "%d", &size);
    element* e = (element*)malloc(sizeof(element)*size);  
    element* ht = (element*)calloc(B, sizeof(element));//해쉬테이블
    for(int i = 0 ;i < size; i++){
        fscanf(fp, "%s %d", e[i].name, &e[i].grade);
    }
    fclose(fp);


    int total_collision = 0;
    for (int i = 0; i < size; i++) {
        int col = insert(ht, e[i]);
        total_collision += col;
    }
    printf("Quadratic probing\n[ N0]name     score   collision\n");
    print_e(ht);
    printf("Total collision: %d\n\n", total_collision);

    printf("Quadratic probing에서의 search결과\n");
    fp = fopen("search.txt", "r");
    char name[20];
    fscanf(fp, "%d", &size);
    for(int i = 0; i < size; i++){
        fscanf(fp, "%s", name);
        int searchcount = search(ht, name);
        if(searchcount){
            printf("%s 있음. 탐색횟수: %d\n", name, searchcount);
        }
        else{
            printf("%s 없음.\n", name);
        }
    }


    fclose(fp);
    free(e);
    free(ht);
}

int h(char* key) {//hash function
    int sum = 0;
    while (*key)
        sum += *key++;
    return sum % B;
}

int insert(element ht[], element e) {
    int home = h(e.name);  //원래 주소
    int collision = 0;

    for (int i = 0; i < B; i++) {
        int bucket = (home + i*i) % B;//quadratic probing

        if (ht[bucket].name[0] == '\0') {  //비어있으면
            ht[bucket] = e;                 //저장
            ht[bucket].collision = collision;
            return collision;
        }
        else {
            collision++;  //충돌 횟수 증가
        }
    }

    return collision;  //꽉 찼을 때
}

void print_e(element* ht){
    for(int i = 0; i < B; i++){
        if(ht[i].name[0] != '\0'){
            printf("[ %2d]%-7s %6d %6d\n", i, ht[i].name, ht[i].grade, ht[i].collision);
        }
        else{
            printf("[ %2d]\n", i);
        }
    }
}

int search(element ht[], char * name){
    int home = h(name);
    for (int i = 0; i < B/2; i++) {
        int bucket = (home + i*i) % B;//quadratic probing

        if (!strcmp(ht[bucket].name, name)) {//같다면
            return i+1;
        }

    }
    return 0;
}