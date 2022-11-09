#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable:4996)

void selectionsort(int* list, int n) //int *list == int list[]
{
	printf("<<<<<<<<<< Selection Sort >>>>>>>>>>\n\n");

	for (int i = 0; i <= n - 2; i++) {
		int min = i;
		for (int j = i + 1; j <= n - 1; j++) {
			if (list[j] < list[min]) {
				min = j;
			}
		}
		int tmp = list[i];
		list[i] = list[min];
		list[min] = tmp;
		printf("%d Pass : ", i + 1);
		for (int i = 0; i < n; i++) {
			printf(" %d", list[i]);
		}
		printf("\n");
	}
}

//  i반복문으로 기준을 정하고, j반복문으로 정한 기준보다 제일 작은 값을 찾아서 swap

int main(void)
{
	int n;
	scanf("%d", &n);

	int* list = (int*)malloc(n * sizeof(int));

	srand(time(NULL));  //난수 seed 변경

	for (int i = 0; i < n; i++) {
		list[i] = rand() % 100;
	}

	printf("Before Sort : ");
	for (int i = 0; i < n; i++) {
		printf(" %d", list[i]);
	}
	printf("\n\n");

	selectionsort(list, n);


	return 0;
}