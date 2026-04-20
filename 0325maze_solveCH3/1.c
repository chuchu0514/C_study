//2023024050 추진성 
#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    short int row;
    short int col;
    short int dir;
}element;

element stack[MAX_STACK_SIZE];//구조체 담는 배열 
int top = -1;
int dx[8] = {-1, -1, 0, 1, 1, 1, 0 ,-1};//북쪽부터 시계방향 
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

element pop() {
    return stack[top--];
}

int isEmpty() {
    return top == -1;
}

void push(element item) {
    stack[++top] = item;
}

int main(){

    char *file[3] = {"maze1.txt", "maze2.txt", "maze3.txt"};
    int row, col;
    for (int i = 0; i < 3; i++) {//파일당 하나씩 순서대로 
        top = -1;
        FILE *fp = fopen(file[i], "r");

        if (fp == NULL) {
            printf("파일 열기 실패\n");//예외처리 
            continue;
        }
        fscanf(fp, "%d %d", &row, &col);//maze배열 크기 입력받기 

        int **maze = (int **)malloc((row+2) * sizeof(int *));//boundary포함이니 +2씩 row col
        for (int i = 0; i < row+2; i++) {
            maze[i] = (int *)malloc((col+2) * sizeof(int));
        }

        int **mark = (int **)malloc((row+2) * sizeof(int *));// mark
        for (int i = 0; i < row+2; i++) {
            mark[i] = (int *)malloc((col+2) * sizeof(int));
        }

        int **path = (int **)malloc((row+2) * sizeof(int *));//최종경로
        for (int i = 0; i < row+2; i++) {
            path[i] = (int *)malloc((col+2) * sizeof(int));
        }
        for(int i =0; i < row + 2; i++){
            for(int j =0; j < col + 2; j++){
                maze[i][j] = 1;
            }
        }//maze 일단 1로 초기화 boundary 처리

        for(int i = 0; i < row + 2; i++){
         for(int j = 0; j < col + 2; j++){
              mark[i][j] = 0;
            }
        }//mark도 초기화 

        printf("[MAZE]\n");
        for(int i = 1; i <= row; i++){
            for(int j = 1; j <= col; j++){
                fscanf(fp,"%d", &maze[i][j]);
                
            }
        }//maze 입력받기 

        int start_x, start_y, final_x, final_y;

        fscanf(fp, "%d %d %d %d", &start_x, &start_y, &final_x, &final_y);//시작위치와 끝위치

        for(int i = 1; i <= row; i++){
            for(int j = 1; j <= col; j++){
                if(i == start_x + 1 && j == start_y + 1){
                    printf("S ");
                    continue;
                }
                else if(i == final_x + 1 && j == final_y + 1){
                    printf("F ");
                    continue;
                }
                printf("%d ", maze[i][j]);
            }
            printf("\n");
        }//MAZE출력 

        element temp;//pop을 받을 임시 구조체 
        int x, y, dir;
        int nx, ny;
        int found = 0;
        push((element){start_x + 1, start_y + 1, 0});// 시작 위치 boundary 고려해서 +1
        mark[start_x + 1][start_y + 1] = 1; //시작위치 방문했음 

        while (!isEmpty()) {
            temp = pop(); 
            x = temp.row;
            y = temp.col;
            dir = temp.dir;

        
            if (x == final_x + 1 && y == final_y + 1) {// 도착점 체크
                found = 1;//찾았음 
                path[x][y] = 1;
            
                for (int i = 0; i <= top; i++) {
                    path[stack[i].row][stack[i].col] = 1; //최종경로 복사 
                }                
                    break;
            }

            while (dir < 8) {
                nx = x + dx[dir];
                ny = y + dy[dir];

                if (nx >= 0 && nx < row + 2 && ny >= 0 && ny < col + 2 && maze[nx][ny] == 0 && mark[nx][ny] == 0) {
                    // 다음 방향을 위한 plan b 현재위치를 저장하는 것 
                    push((element){x, y, dir + 1});

                    // 방문 표시
                    mark[nx][ny] = 1;

                    // 다음 위치로 이동
                    push((element){nx, ny, 0});

                    break;
                }

                dir++;
            }
        }
        if (found) {
            printf("\n[PATH]\n"); //경로 출력 

           
            for(int i = 1; i <= row; i++){
                for(int j = 1; j <= col; j++){
                if (i == start_x+1 && j == start_y+1)
                    printf("S ");
                else if (i == final_x+1 && j == final_y+1)
                    printf("F ");
                else if (path[i][j] == 1)
                    printf("X ");
                else
                    printf("%d ", maze[i][j]);
                }
                printf("\n");
            }
        }
        else {
            printf("\nNo Path\n");
        }
        printf("\n");
    }
}

