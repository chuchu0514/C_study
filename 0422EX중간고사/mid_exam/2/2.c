#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* next;
}node;

void insert(node** head, int data);
void print_node(node* head);
void func(node** head, int x, int y);

int main() {
	FILE* fp = fopen("in2.txt", "r");
	if (fp == NULL) {
		printf("error");
		return 0;
	}
	node* head = NULL;
	int size = 0;
	int num;
	fscanf(fp, "%d", &size);
	for (int i = 0;i < size; i++) {
		fscanf(fp, "%d", &num);
		insert(&head, num);
	}
	printf("(1)Print List: ");
	print_node(head);
	printf("\n");
	int x, y;
	printf("(2)Enter X, Y: ");
	scanf("%d %d", &x, &y);
	func(&head, x, y);
	return 0;
}

void insert(node** head, int data) {
	node* newnode = (node*)malloc(sizeof(node));
	newnode->data = data;

	if (*head == NULL) {
		newnode->next = NULL;
		*head = newnode;
		return;
	}
	newnode->next = *head;
	*head = newnode;
	return;
}
void print_node(node* head) {
	node* cur = head;
	while (cur != NULL) {
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");
	return;
}

void func(node** head, int x, int y) {
	node* cur = *head;
	node* prev = NULL;

	while (cur != NULL) {

		if (cur->data <= y && cur->data >= x) {
			node* temp = cur;
			if (prev == NULL) {
				printf("Delete %d...", cur->data);
				cur = cur->next;
				*head = temp->next;
				print_node(*head);
				free(temp);

			}
			else {
				printf("Delete %d...", cur->data);
				prev->next = cur->next;
				print_node(*head);
				cur = cur->next;
				free(temp);
			}

		}
		else {
			prev = cur;
			cur = cur->next;

		}
	}
}