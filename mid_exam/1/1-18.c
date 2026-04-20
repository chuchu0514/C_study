#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void print_recur(int num, int count, int k);

int main() {
	int num;
	printf("Enter N: ");
	scanf("%d", &num);
	print_recur(num, 0, num);

	return 0;
}

void print_recur(int num, int count, int k) {

	if (count == num * 2) {
		return;
	}
	if (count < num) {
		for (int i = 0; i < k; i++) {
			printf("*");
		}
		printf("\n");
		count++;
		print_recur(num, count, k - 1);
	}
	else if (count == num) {
		count++;
		k = k + 1;
		print_recur(num, count, k);
	}
	else {
		k = k + 1;
		for (int i = 0; i < k; i++) {
			printf("*");
		}
		printf("\n");
		count++;
		print_recur(num, count, k);

	}

}