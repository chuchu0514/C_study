#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* next;
}node;

void insert(node** head, int data);
void merge(node** head1, node** head2, int size1);
void print_node(node* head);
void sort(node** head);

int main() {
	FILE* fp = fopen("a1.txt", "r");
	int size1, size2;
	int num;
	fscanf(fp, "%d", &size1);
	node* head1 = NULL, * head2 = NULL;
	for (int i = 0;i < size1; i++) {
		fscanf(fp, "%d", &num);
		insert(&head1, num);
	}
	fclose(fp);
	fp = fopen("a2.txt", "r");
	fscanf(fp, "%d", &size2);
	for (int i = 0;i < size2; i++) {
		fscanf(fp, "%d", &num);
		insert(&head2, num);
	}
	fclose(fp);
	sort(&head1);
	sort(&head2);
	printf("List1: ");
	print_node(head1);
	printf("List2: ");
	print_node(head2);
	merge(&head1, &head2, size1);
	sort(&head1);
	printf("Merged: ");
	print_node(head1);


}

void insert(node** head, int data) {
	node* newnode = (node*)malloc(sizeof(node));
	newnode->data = data;
	newnode->next = NULL;

	if (*head == NULL) {
		*head = newnode;
		return;
	}
	node* cur = *head;
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = newnode;
	return;

}
void merge(node** head1, node** head2, int size1) {
	node* cur = *head1;
	for (int i = 0; i < size1; i++) {
		node* prev = NULL;
		node* cur2 = *head2;
		while (cur2 != NULL) {
			if (cur->data == cur2->data) {
				node* temp = cur2;
				if (prev == NULL) {
					*head2 = cur2->next;
				}
				else {
					prev->next = cur2->next;
				}
				cur2 = cur2->next;
				free(temp);
			}
			else {
				prev = cur2;
				cur2 = cur2->next;
			}

		}
		cur = cur->next;
	}

	node* cur3 = *head1;
	while (cur3->next != NULL) {
		cur3 = cur3->next;
	}
	cur3->next = *head2;
	return;
	}

void print_node(node* head) {
	node* cur = head;
	while (cur != NULL) {
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");
}
void sort(node** head) {
	int temp;
	int swapped;
	do {
		swapped = 0;
		node* cur = *head;
		while (cur->next != NULL) {
			if (cur->data > cur->next->data) {
				temp = cur->data;
				cur->data = cur->next->data;
				cur->next->data = temp;
				swapped = 1;
			}
			cur = cur->next;
		}

	} while (swapped);
}