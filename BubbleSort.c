#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable:4996)

#define FALSE 0
#define TRUE 1


void bubblesort(int* list, int n) //int *list == int list[]
{
	printf("<<<<<<<<<< Bubble Sort >>>>>>>>>>\n\n");

	for (int i = n - 1; i > 0; i--) {
		int flag = FALSE;
		for (int j = 0; j < i; j++) {
			if (list[j] > list[j + 1]) {
				int tmp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = tmp;
				flag = TRUE;
			}
		}

		if (flag == FALSE) break;

		printf("%d Pass : ", n - i);
		for (int i = 0; i < n; i++) {
			printf(" %d", list[i]);
		}
		printf("\n");

	}
}


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

	bubblesort(list, n);


	return 0;
}