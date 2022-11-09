#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable:4996)

//�ܺ����� : �ʿ��� �κи� �����ͼ� ���� (-> �պ�����)
//�������� : ��ǻ�� �����Ϳ� ������ �����͸� ��� �÷��ΰ� ����

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

	if (i > mid)  //i�� ���� �� ��������
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

	for (l = left; l <= right; l++) {    //L1�� �� ���� => ���߿� �����
		L1[l] = L2[l];
	}

}
void mergeSort(int* L1, int* L2, int left, int right)
{
	int mid;
	if (left < right) //���� �����ϴٸ�
	{
		mid = (left + right) / 2;
		mergeSort(L1, L2, left, mid);
		mergeSort(L1, L2, mid + 1, right);

		merge(L1, L2, left, mid, right);                //�����ؼ� ��ġ��
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

	mergeSort(L1, L2, 0, n - 1); // ����Լ� ó�� ���� (0���� n-1����)
	printList(L2, n);


	return 0;
}