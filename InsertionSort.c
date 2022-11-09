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

//  n번째부터 (2부터시작) 기준을 잡고 그 앞쪽으로 자신보다 작은게 나올때 까지 덮어쓰기
//  덮어쓰다가 자기보다 앞에 작은게 나오면 그 앞자리에 key값 (n번째 값 덮기)

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

	insertionsort(list, n);


	return 0;
}