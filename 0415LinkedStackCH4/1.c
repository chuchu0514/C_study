//2023024050 추진성
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
	int data;
	struct stack* next;
 }stack;

stack *sta[3];//문서보관함 세 개 

void add(stack** sta, int target);
void delete(stack** sta);
void print_sta(stack* sta);

int main() {
	FILE* fp = fopen("in.txt", "r");
	if (fp == NULL) {
		printf("파일 열기 실패\n");
		return 1;
	}
	char c;
	int index, target;
	stack* head1 = NULL, * head2 = NULL, * head3 = NULL;
	sta[0] = head1;
	sta[1] = head2;
	sta[2] = head3;

	while (1) {
		fscanf(fp, " %c", &c);
		if (c == 'q') {
			break;
		}

		if(c == 'a'){
			fscanf(fp, " %d", &index);
			fscanf(fp, " %d", &target);
			add(&sta[index], target);
			printf("(a %d %d) box[%d]: ", index, target, index);
			print_sta(sta[index]);
		}
		else if (c == 'd') {
			fscanf(fp, " %d", &index);
			printf("(d %d) box[%d]: ", index, index);
            if(sta[index] == NULL){//삭제할 수 없는 경우 delete함수 아예 작동 x
        		printf("Cannot delete\n");
            }
            else{
			    delete(&sta[index]);
			    print_sta(sta[index]);
            }
		}


	}
    for (int i = 0; i < 3; i++) {//동적할당 해제 
    while (sta[i] != NULL) {
        stack* temp = sta[i];
        sta[i] = sta[i]->next;
        free(temp);
    }
}
	fclose(fp);
}

void add(stack** sta, int target) {

	stack* newnode = (stack*)malloc(sizeof(stack));
	newnode->data = target;
	if (*sta == NULL) { //첫 add인 경우 
		newnode->next = NULL;
		*sta = newnode;
		return;
	}
	newnode->next = *sta;
	*sta = newnode;
	return;
}

void delete(stack** sta) {
	if (*sta == NULL) {
		return;
	}

	stack* temp = *sta;
	*sta = (*sta)->next;
	free(temp); 
}

void print_sta(stack* sta) {
	if (sta == NULL) {
		printf("Empty\n");
		return;
	}
	stack* cur = sta;
	while (cur != NULL) {
		printf("%d ", cur->data);
		cur = cur->next;
	}
    printf("\n");
	return;
}
