#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable:4996)

#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))

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

int partition(int* L, int left, int right, int k)
{
	int pivot, temp, low, high;
	pivot = L[k];

	low = left - 1;
	high = right;

	SWAP(L[k], L[high], temp); //pivot을 제일 오른쪽으로 보내줌 (편하게 하기위해서?)


	do
	{
		do {
			low++;
		} while (L[low] < pivot);

		do {
			high--;
		} while (L[high] > pivot);

		if (low < high) {
			SWAP(L[low], L[high], temp);
		}

	} while (low < high);
	SWAP(L[low], L[right], temp);

	return low;
}

void quickSort(int* L, int left, int right)
{
	if (left < right)
	{
		int k = (rand() % (right - left + 1)) + left;  //임의의 pivot 위치 k
		int q = partition(L, left, right, k); //q는 알아서 정렬된다 (자기보다 작은것은 왼쪽, 큰건 오른쪽)
		quickSort(L, left, q - 1);
		quickSort(L, q + 1, right);
	}
}

int main(void)
{
	int n;
	scanf("%d", &n);

	int* L = (int*)malloc(sizeof(int) * n);

	srand(time(NULL));

	makeList(L, n);
	printList(L, n);


	quickSort(L, 0, n - 1);
	printList(L, n);


	return 0;
}