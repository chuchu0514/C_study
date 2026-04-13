#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_reverse(char * c, int size);

int main(){

    char c[100];
    int size;
    while(1){
        scanf("%s", c);
        if(strcmp(c, "Q") == 0){
            break;
        }
        size = strlen(c);
        print_reverse(c, size);
    }
}

void print_reverse(char * c, int size){

    if (size == 0){
        return;
    }
    printf("%c", c[size-1]);

    print_reverse(c, size-1);
}