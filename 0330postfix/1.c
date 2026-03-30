//2023024050 추진성
#define _CRT_SECURE_NO_WARNINGS
#define MAX 100
#include <stdio.h>
#include <stdlib.h>

char stack[MAX];
int top = -1;

void push(char x){
    if (top < MAX - 1)
    stack[++top] = x;
}
int isEmpty(){
    return top == -1;
}
char pop(){
    if(!isEmpty()){
        return stack[top--];
    }
    else{
        printf("stack is empty");
        return '\0';
    }
}
char peek(){
    if(!isEmpty()){
        return stack[top];
    }
    else{
        printf("stack is empty");
        return '\0';
    }    
}
int precedence(char op);
void infix_to_postfix(char infix[], char postfix[]);
int is_operator(char c){
    return c=='+' || c=='-' || c=='*' || c=='/' || c=='%';
}

int is_operand(char c){
    return c >= '0' && c <= '9';
}

int main() {

    FILE *fp= fopen("infix.txt","r");
    int num;
    fscanf(fp,"%d", &num);
    char ** infix = (char **)malloc(sizeof(char*)*num); //동적할당 
    for(int i = 0; i < num ; i++){
        infix[i] = malloc(sizeof(char)*MAX);
    }
    char ** postfix = (char **)malloc(sizeof(char*)*num);
    for(int i = 0; i < num ; i++){
        postfix[i] = malloc(sizeof(char)*MAX);
    }
    for(int i = 0; i < num ; i++){ //infix입력받기
        fscanf(fp, "%s", infix[i]);
    }
    fclose(fp);

    for(int i = 0; i < num ; i++){
        printf("Infix: %s\n", infix[i]); //출력구문
        top = -1;//함수 실행 전 스택 비워주기 
        infix_to_postfix(infix[i], postfix[i]);//postfix로 변환하는 함수 
    }

    for(int i = 0; i < num ; i++){
        free(infix[i]); //할당해제 
        free(postfix[i]);
    }
    free(infix);
    free(postfix);

    return 0;
}
int precedence(char op){
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/' || op == '%') return 2;
    return 0;
}

void infix_to_postfix(char infix[], char postfix[]) {

    int i, j = 0;
    char c;
    char prev = '\0';

    for (i = 0; infix[i] != '\0'; i++) {//\0문자가 나올때까지 =문자열 끝까지

        c = infix[i];

        //에러처리 참조규칙 
        if (is_operator(c)) {//현재 토큰이 binary operator일 경우..
            if (!(is_operand(prev) || prev == ')')) {
                postfix[j] = '\0';
                printf("Postfix: %s\n", postfix);
                printf("Error token:%c\n\n", c);
                return;
            }
        }

 
        if (is_operand(c)) {//operand일 경우
            if (is_operand(prev) || prev == ')') {
                postfix[j] = '\0';
                printf("Postfix: %s\n", postfix);
                printf("Error token:%c\n\n", c);
                return;
            }
        }

        // 3. '('
        if (c == '(') {
            if (is_operand(prev)) {
                postfix[j] = '\0';
                printf("Postfix: %s\n", postfix);
                printf("Error token:%c\n\n", c);
                return;
            }
        }

        // 4. ')'
        if (c == ')') {
            if (!(is_operand(prev) || prev == ')')) {
                postfix[j] = '\0';
                printf("Postfix: %s\n", postfix);
                printf("Error token:%c\n\n", c);
                return;
            }
        }


        // 피연산자
        if (is_operand(c)) {
            postfix[j++] = c;
        }

        // '('
        else if (c == '(') {
            push(c);
        }

        // ')'
        else if (c == ')') {
            while (!isEmpty() && peek() != '(') {// )가 나오면 (가 나오기 전까지 스택을 다 비우고 (는 저장하지 말고 따로 제거 
                postfix[j++] = pop();
            }
            pop(); // '(' 제거
        }

        // 연산자
        else {
            while (!isEmpty() && peek() != '(' &&
                   precedence(peek()) >= precedence(c)) {//c가 먼저 들어간 것보다 우선순위가 낮다면 
                postfix[j++] = pop();
            }
            push(c);//높다면 다시 스택에 push
        }

        prev = c;//이전 char로 됨 
    }

    //eos확인
    if (is_operator(prev) || prev == '(') {
        postfix[j] = '\0';
        printf("Postfix: %s\n", postfix);
        printf("Error token: eos\n");
        return;
    }

    
    while (!isEmpty()) { //스택 비우기 
        postfix[j++] = pop();
    }

    postfix[j] = '\0';//문자열 끝 

    printf("Postfix: %s\n\n", postfix);
}