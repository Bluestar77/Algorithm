#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable:4996)

void insertionsort(int* list, int n) //int *list == int list[]
{
	printf("<<<<<<<<<< Insertion Sort >>>>>>>>>>\n\n");

	for (int i = 1; i <= n - 1; i++) {
		int key = list[i];

		int j = i - 1;
		while (j >= 0 && list[j] > key)
		{
			list[j + 1] = list[j];
			j--;
		}


		/*
		for (int j = i - 1; j>=0 && list[j] > key; j--) {
			list[j + 1] = list[j];
		}
		*/

		list[j + 1] = key;

		printf("%d Pass : ", i);
		for (int i = 0; i < n; i++) {
			printf(" %d", list[i]);
		}
		printf("\n");
	}
}

//  n��°���� (2���ͽ���) ������ ��� �� �������� �ڽź��� ������ ���ö� ���� �����
//  ����ٰ� �ڱ⺸�� �տ� ������ ������ �� ���ڸ��� key�� (n��° �� ����)

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

	insertionsort(list, n);


	return 0;
}