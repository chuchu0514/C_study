#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 20
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char stack[MAX_SIZE];
int top = -1;

void push(char c){
    stack[++top] = c;
    return;
}

char pop(){
    return stack[top--];
}

int main(){

    FILE* fp = fopen("in.txt", "r");
    int num;

    fscanf(fp, "%d\n", &num);
    char c[100];

    for (int i = 0; i < num; i++) {
        top = -1;

        int idx = 0;
        fgets(c, sizeof(c), fp);

            for(int i = 0; i < strlen(c); i++){

                if (c[i] == '\n'){
                    printf("X\n");
                    break;
                }
                if (c[i] == '(') {
                    push(c[i]);
                }
                else if (c[i] == ')') {
                    if (top >= 0) pop();
                    else {
                        printf("%d\n", idx);
                        break;
                    }
                }

                idx++;
        
            }

        }
    
    fclose(fp);
    return 0;
}