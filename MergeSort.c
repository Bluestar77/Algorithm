#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable:4996)

//외부정렬 : 필요한 부분만 가져와서 정렬 (-> 합병정렬)
//내부정렬 : 컴퓨터 데이터에 정렬할 데이터를 모두 올려두고 정렬

void makeList(int* L, int n)
{
	for (int i = 0; i < n; i++) {
		L[i] = rand() % 100;
	}
}

void printList(int* L, int n)
{
	for (int i = 0; i < n; i++) {
		printf(" %d", L[i]);
	}
	printf("\n");
}

void merge(int* L1, int* L2, int left, int mid, int right)
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	while (i <= mid && j <= right) {
		if (L1[i] <= L1[j]) {
			L2[k++] = L1[i++];
		}
		else {
			L2[k++] = L1[j++];
		}
	}

	if (i > mid)  //i쪽 값이 다 빠졌으면
	{
		for (l = j; l <= right; l++) {
			L2[k++] = L1[l];
		}
	}
	else
	{
		for (l = i; l <= mid; l++) {
			L2[k++] = L1[l];
		}
	}

	for (l = left; l <= right; l++) {    //L1에 값 저장 => 나중에 써야함
		L1[l] = L2[l];
	}

}
void mergeSort(int* L1, int* L2, int left, int right)
{
	int mid;
	if (left < right) //분할 가능하다면
	{
		mid = (left + right) / 2;
		mergeSort(L1, L2, left, mid);
		mergeSort(L1, L2, mid + 1, right);

		merge(L1, L2, left, mid, right);                //정렬해서 합치기
	}
}

int main(void)
{
	int n;
	scanf("%d", &n);

	int* L1 = (int*)malloc(sizeof(int) * n);
	int* L2 = (int*)malloc(sizeof(int) * n);

	srand(time(NULL));

	makeList(L1, n);

	printList(L1, n);

	mergeSort(L1, L2, 0, n - 1); // 재귀함수 처음 범위 (0부터 n-1까지)
	printList(L2, n);


	return 0;
}