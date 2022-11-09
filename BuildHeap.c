#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable:4996)

//����� ������ : �ϴ� �����͸� �� ����Ʈ���� �����ϰ�, ������ ����������

#define SIZE 100

typedef struct {
	int n;
	int H[SIZE];
}Heap;

void init(Heap* heap) //��� ���� 0�� �ʱ�ȭ
{
	heap->n = 0; //   (*heap).n = 0
	for (int i = 0; i < SIZE; i++) {
		heap->H[i] = 0;
	}
}

void downHeap(Heap* heap, int i)
{
	if (i * 2 > heap->n) //�����ڽ��� ������
		return; //�ٿ��� ���ʿ� ����

	if (heap->H[i] < heap->H[i * 2] || heap->H[i] < heap->H[i * 2 + 1]) //�ڽ��� ������ ũ�� (�ٲ������)
	{
		if (heap->H[i * 2] > heap->H[i * 2 + 1]) { //�����ڽ��� �� ũ��
			int tmp = heap->H[i];
			heap->H[i] = heap->H[i * 2];
			heap->H[i * 2] = tmp;
			downHeap(heap, i * 2);
		}
		else {  //������ �ڽ��� �� ũ��
			int tmp = heap->H[i];
			heap->H[i] = heap->H[i * 2 + 1];
			heap->H[i * 2 + 1] = tmp;
			downHeap(heap, i * 2 + 1);
		}
	}
	else
		return;

}

/*
void rBuildHeap(Heap* heap)   //������� ����� ������
{
	for (int i = heap->n/2; i>0;i--){
		downheap(heap,1);
	}
}

�ٿ����� �����Ϸ��� ���������/2 ���� �������� �ٿ������� �Ѵ�
=> �ٿ����� �����ϴ� = (�ּ�) ���� �ڽĳ�尡 �����Ѵ� = n*2�� �����Ѵ� (�ּ� ���������)

*/

void rBuildHeap(Heap* heap, int i)
{
	if (i > heap->n)  //�������̸� ������
		return;
	if (i * 2 <= heap->n) {  //�����ڽ��� �����ϸ�
		rBuildHeap(heap, i * 2); //�������� ����
	}
	if (i * 2 + 1 <= heap->n) {  //������ �ڽ��� �����ϸ�
		rBuildHeap(heap, i * 2 + 1); //������ �ڽ����� ����
	}
	downHeap(heap, i);  //���̻� �������� ������ �ٿ���

}

void printHeap(Heap* heap)
{
	for (int i = 1; i <= heap->n; i++) {
		printf(" [%d] ", heap->H[i]);
	}
	printf("\n");
}

void insertItem(Heap* heap, int k)
{
	heap->n++;  //��� ���� ����
	heap->H[heap->n] = k;
}

int main(void)
{
	Heap heap;
	init(&heap);

	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		int k = rand() % 100;
		insertItem(&heap, k);
		printf(" [%d]", k);
	}
	printf("\n");

	rBuildHeap(&heap, 1);
	printHeap(&heap);


	return 0;
}