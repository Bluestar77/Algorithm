#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable:4996)

//제자리 힙정렬 알고리즘 : 힙으로 정렬된 배열을 크기순으로 정렬한다

#define SIZE 100

typedef struct {
	int n;
	int H[SIZE];
}Heap;

void init(Heap* heap) //노드 개수 0개 초기화
{
	heap->n = 0; //   (*heap).n = 0
	for (int i = 0; i < SIZE; i++) {
		heap->H[i] = 0;
	}
}

void downHeap(Heap* heap, int i)
{
	if (i * 2 > heap->n) //왼쪽자식이 없으면
		return; //다운힙 할필요 없음

	if (heap->H[i] < heap->H[i * 2] || heap->H[i] < heap->H[i * 2 + 1]) //자식이 나보다 크면 (바꿔줘야함)
	{
		if (heap->H[i * 2] > heap->H[i * 2 + 1]) { //왼쪽자식이 더 크면
			int tmp = heap->H[i];
			heap->H[i] = heap->H[i * 2];
			heap->H[i * 2] = tmp;
			downHeap(heap, i * 2);
		}
		else {  //오른쪽 자식이 더 크면
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
void rBuildHeap(Heap* heap)   //비재귀적 상향식 힙생성
{
	for (int i = heap->n/2; i>0;i--){
		downheap(heap,1);
	}
}

다운힙이 가능하려면 마지막노드/2 부터 앞쪽으로 줄여나가야 한다
=> 다운힙이 가능하다 = (최소) 왼쪽 자식노드가 존재한다 = n*2가 존재한다 (최소 마지막노드)

*/

void rBuildHeap(Heap* heap, int i)
{
	if (i > heap->n)  //마지막이면 끝내라
		return;
	if (i * 2 <= heap->n) {  //왼쪽자식이 존재하면
		rBuildHeap(heap, i * 2); //왼쪽으로 보냄
	}
	if (i * 2 + 1 <= heap->n) {  //오른쪽 자식이 존재하면
		rBuildHeap(heap, i * 2 + 1); //오른쪽 자식으로 보냄
	}
	downHeap(heap, i);  //더이상 보낼곳이 없으면 다운힙

}

int removeMax(Heap* heap)
{
	int k = heap->H[1];
	heap->H[1] = heap->H[heap->n];
	heap->n--;
	downHeap(heap, 1);
	return k;
}

void inPlaceHeapSort(Heap* heap)
{
	int size = heap->n;
	int key;

	for (int i = 0; i < size; i++) {
		key = removeMax(heap);
		heap->H[heap->n + 1] = key;
	}

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
	heap->n++;  //노드 개수 증가
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

	int n = heap.n;
	inPlaceHeapSort(&heap);

	for (int i = 1; i <= n; i++) {
		printf(" [%d]", heap.H[i]);
	}
	printf("\n");


	return 0;
}