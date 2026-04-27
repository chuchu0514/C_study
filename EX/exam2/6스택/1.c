//16분
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char stack[100];
int top = -1;
char pop(){
    if(top == -1){
        return '\0';
    }
    return stack[top--];
}
void push(char item){
    stack[++top] = item;
    return;
}

void check(char* str);

int main(){
    FILE *fp = fopen("a1.txt", "r");
    char str[100];
    while(fgets(str, 100, fp) != NULL){
        if(str[strlen(str)-1] == '\n')
            str[strlen(str)-1] = '\0';  
        printf("%s: ", str);
        check(str);
    }

    fclose(fp);
}

void check(char* str){
    top = -1;
    for(int i = 0; i < strlen(str); i++){
        push(str[i]);
    }

    for(int i = 0; i < strlen(str); i++){
        
        if(str[i] != pop()){
            printf("No \n");
            return;
        }
    }
    printf("Yes \n");
    return;
}