#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable:4996)
// 8주차 해시테이블
// 분리연쇄법 알고리즘 (연결리스트, 충돌X)

#define M 13

typedef struct HashNode
{
	int key;
	struct HashNode* next;
}HashNode;

void init(HashNode* H)  //해쉬배열 초기화
{
	for (int i = 0; i < M; i++) {
		H[i].key = 0;
		H[i].next = NULL;
	}
}

int h(int k)
{
	return k % M;
}

void insertItem(HashNode* H, int k)
{
	int v = h(k);
	HashNode* node = (HashNode*)malloc(sizeof(HashNode));
	node->key = k;
	node->next = H[v].next;
	H[v].next = node;  //새로 들어온 애가 첫번째로
}

void print(HashNode* H)
{ //밖은 H[M]배열로 돌고 안에서는 리스트로 돌고
	for (int i = 0; i < M; i++)
	{
		printf("H[%02d] : ", i);
		for (HashNode* p = H[i].next; p != NULL; p = p->next)
		{
			printf("(%d) ", p->key);
		}
		printf("\n");
	}
}

int removeElement(HashNode* H, int k) //지워진 개수 리턴
{
	int v = h(k);  //키의 배열 넘버(v)를 찾는다
	int count = 0;
	HashNode* p = &H[v]; //배열 네모 자체를 가르킴 H[v]
	HashNode* q;

	while (p->next != NULL) //버킷에 슬랏이 달려있으면
	{
		if (p->next->key == k) //삭제하려는 값이면
		{
			count++;
			q = p->next;  //q에 삭제할값 대입
			p->next = q->next;  //q의 다음을 p의 다음이 가르키도록 (=q뛰어넘고 연결)
			free(q); //q삭제
		}
		else {
			p = p->next;
		}
	}
	return count;
}

int findElement(HashNode* H, int k) {
	int v = h(k);
	int count = 0;
	HashNode* p = &H[v];

	for (p = H[v].next; p != NULL; p = p->next)
	{
		if (p->key == k)
			count++;
	}
	return count;
}

int main(void)
{
	HashNode H[M];
	init(H);

	srand(time(NULL));

	for (int i = 0; i < 20; i++) {
		insertItem(H, rand() % 50 + 10);
	}

	print(H);

	int k;

	printf("\nSearch Key : ");
	scanf("%d", &k);
	printf("%d개의 %d find.\n\n", findElement(H, k), k);

	printf("\nInput Remove Key : ");
	scanf("%d", &k);
	printf("%d개의 %d deleted.\n\n", removeElement(H, k), k);
	print(H);

	return 0;
}