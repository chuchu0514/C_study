//2023024050 추진성
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(){

    char *file[3] = {"q1.txt", "q2.txt", "q3.txt"};
    for(int i = 0; i < 3; i++){
        FILE * fp = fopen(file[i],"r");

        int size;
        fscanf(fp, "%d", &size);
        printf("Queue Size: %d\n\n", size);

        int *queue = malloc(sizeof(int)*size); //linear queue
        int *cir_queue = malloc(sizeof(int)*size);//원형큐 
        char c = 0;//입력받을문자
        int num;//data

        int cfront = 0, crear = 0;//원형큐의 front와 rear
        int front = 0, rear = -1;//linear큐의 front와 rear

        while(c != 'q'){//q일때 그만 
            fscanf(fp, " %c", &c);
            if(c == 'a'){ //add의 경우
                fscanf(fp, "%d", &num);
                printf("add %d...\n",num);
                printf("[Circular queue] ");
                if((crear+1) % size == cfront){//가득 찬 조건 
                    printf("Full.\n");
                }
                else{
                    crear = (crear + 1) % size;//rear를 먼저 늘리고 (원형이니까 size로 나눔)
                    cir_queue[crear] = num;//값 할당 
                    for(int i = cfront; i != crear; i = (i+1) % size){
                        printf("%d ", cir_queue[(i+1) % size]);
                    }
                    printf("\n");
                }
                printf("[Linear queue] ");
                if(rear == size - 1 && front > 0){ //cannot add의 조건 
                    printf("Cannot add.\n");
                }
                else if(rear == size - 1 && front == 0){//가득 찬 조건 
                    printf("Full.\n");
                }
                else{
                    queue[++rear] = num;
                    for(int i = front; i <= rear; i++){
                        printf("%d ", queue[i]);
                    }
                    printf("\n");                    
                }
            }
            else if(c == 'd')
            {
                printf("Delete\n");
                printf("[Circular queue] ");
                if(cfront == crear){ //빈 조건 
                    printf("Empty.\n");
                }
                else{
                    cfront = (cfront + 1) % size;  
                    if(cfront == crear){//만약 del하고서 출력할 게 없다면 
                        printf("Empty.\n");
                    }
                    else{
                        for(int i = cfront; i != crear; i = (i+1) % size){
                            printf("%d ", cir_queue[(i+1) % size]);
                        }
                        printf("\n");
                    }
                }
                printf("[Linear queue] ");
                if(front > rear){ //빈 조건 
                    printf("Empty.\n");
                }
                else{
                    if(front > rear){//만약 del하고서 출력할 게 없다면 
                        printf("Empty.\n");
                    }
                    else {
                        for(int i = front; i <= rear; i++){
                            printf("%d ", queue[i]);
                        }
                        printf("\n");
                    }
                }
            }
        }
        printf("\n");
        fclose(fp);
        free(cir_queue);
        free(queue);
    }
}