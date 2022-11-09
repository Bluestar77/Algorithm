#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable:4996)

//1�� ������ �� ���� ���� ����������
//���Ը��� ������ (������)

#define SIZE 100
//��������Ʈ���� ������� ���� ������
//�迭�� �����ϴ°� ����.

typedef struct {
	int n;
	int H[SIZE];
}Heap;

void init(Heap* heap) //��� ���� 0�� �ʱ�ȭ
{
	heap->n = 0; //   (*heap).n = 0
}

void Upheap(Heap* heap)
{
	int i = heap->n;    //���� Upheap �ؾ��ϴ� �ε��� ��ȣ
	int k = heap->H[i]; //���� Upheap �ؾ��ϴ� ��

	while ((i != 1) && (k < heap->H[i / 2]))   // (i�� 1�̸� ��Ʈ) && (�θ��� Ű���� ��)
	{
		heap->H[i] = heap->H[i / 2];
		i /= 2;
	}
	heap->H[i] = k;
}

void downHeap(Heap* heap)
{
	int k = heap->H[1];
	int p = 1, c = 2;  //p�� ����(��Ʈ), c�� �����ڽ�

	while (c <= heap->n)
	{
		if ((c < heap->n) && (heap->H[c] > heap->H[c + 1]))   //(�������� �ִٸ�) && (�� �������� ���ʺ��� �۴ٸ�)
		{
			c++;  //������ �ڽ����� ������ش�
		}
		if (k <= heap->H[c]) break;  //�ٲ� �ʿ� ������ ��������

		heap->H[p] = heap->H[c];
		p = c;
		c *= 2;
	}
	heap->H[p] = k;
}

int removeMin(Heap* heap)    //������ ��� �ִ������� Ȯ���ؾ���!!
{
	int k = heap->H[1];
	heap->H[1] = heap->H[heap->n];
	heap->n--;

	downHeap(heap);
	return k;
}

void printHeap(Heap* heap)
{
	for (int i = 1; i <= heap->n; i++) {
		printf("%d ", heap->H[i]);
	}
	printf("\n");
}

void insertItem(Heap* heap, int k)
{
	heap->n++;  //��� ���� ����
	heap->H[heap->n] = k;
	Upheap(heap);
}

int main(void)
{
	Heap heap;
	init(&heap);
	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
		int k = rand() % 100;
		insertItem(&heap, k);
		printf("%d ", k);
	}
	printf("\n");

	printHeap(&heap);

	printf("\n");

	printf("Min : %d\n", removeMin(&heap));
	printHeap(&heap);

	return 0;
}