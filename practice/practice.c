#define MAX 5

int stack[MAX];
int top = -1;

void push(int x){
    if (top == MAX - 1){
        printf("꽉참");
        return;
    }

    top++;
    stack[top] = x;
}

int pop(){
    if (top == -1){
        printf("비었음");
        return -1;
    }
    int a = stack[top];
    top--;

    return a;
}

