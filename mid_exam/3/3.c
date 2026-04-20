#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 20
#include <stdio.h>
#include <stdlib.h>

char stack[MAX_SIZE];
top = -1;

void push(int item) {
	stack[++top] = item;
	return;
}

char pop() {
	return stack[top--];
}
int isempty() {
	return top == -1;
}

void count_valid(char* s);

int main() {
	FILE* fp = fopen("in3.txt", "r");
	int size;
	
	fscanf(fp, "%d", &size);
	char arr[100];
	for (int i = 0; i < size; i++) {
		fscanf(fp, "%s", arr);
		count_valid(arr);
	}
	return 0;
}

void count_valid(char* s) {
	printf("%s\n", s);
	int size = strlen(s);
	top = -1;
	char c = '\0';

	for (int i = 0; i < size; i++) {
		c = s[i];
		if (c == '0') {
			push(c);
		}
		else if(c == '1') {
			if (!isempty()) {
				pop();
			}
			else {
				printf("==> Invalid\n");
				return;
			}
		}
	}

	if (!isempty()) {
		printf("==> Invalid\n");

	}
	else {
		printf("==> Valid\n");

	}





	return;
}


