#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


void print_recur(int n, int count, int i);
int main(){
    int num;
    int count = 0;
    int i = 1;
    scanf("%d", &num);
    print_recur(num, count, i);
    
}
void print_recur(int n, int count, int i){

    if(count >= 2 * n - 1){
        return;
    }

    if(count < n - 1){
        printf("%d ", i);
        count++;
        i++;
        print_recur(n, count, i);
    }
    else{
        printf("%d ", i);
        count++;
        i--;
        print_recur(n, count, i);
    }
}