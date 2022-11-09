#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable:4996)

//1개 삽입할 때 마다 힙을 만들어버린다
//삽입마다 힙정렬 (힙생성)

#define SIZE 100
//완전이진트리는 빈공간이 없기 때문에
//배열로 구현하는게 좋다.

typedef struct {
	int n;
	int H[SIZE];
}Heap;

void init(Heap* heap) //노드 개수 0개 초기화
{
	heap->n = 0; //   (*heap).n = 0
}

void Upheap(Heap* heap)
{
	int i = heap->n;    //현재 Upheap 해야하는 인덱스 번호
	int k = heap->H[i]; //현재 Upheap 해야하는 값

	while ((i != 1) && (k < heap->H[i / 2]))   // (i가 1이면 루트) && (부모의 키값과 비교)
	{
		heap->H[i] = heap->H[i / 2];
		i /= 2;
	}
	heap->H[i] = k;
}

void downHeap(Heap* heap)
{
	int k = heap->H[1];
	int p = 1, c = 2;  //p는 시작(루트), c는 왼쪽자식

	while (c <= heap->n)
	{
		if ((c < heap->n) && (heap->H[c] > heap->H[c + 1]))   //(오른쪽이 있다면) && (그 오른쪽이 왼쪽보다 작다면)
		{
			c++;  //오른쪽 자식으로 만들어준다
		}
		if (k <= heap->H[c]) break;  //바꿀 필요 없으면 끝내버림

		heap->H[p] = heap->H[c];
		p = c;
		c *= 2;
	}
	heap->H[p] = k;
}

int removeMin(Heap* heap)    //삭제할 노드 있는지부터 확인해야함!!
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
	heap->n++;  //노드 개수 증가
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