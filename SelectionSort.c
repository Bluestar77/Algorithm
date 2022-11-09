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

//  i�ݺ������� ������ ���ϰ�, j�ݺ������� ���� ���غ��� ���� ���� ���� ã�Ƽ� swap

int main(void)
{
	int n;
	scanf("%d", &n);

	int* list = (int*)malloc(n * sizeof(int));

	srand(time(NULL));  //���� seed ����

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