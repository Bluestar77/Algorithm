#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable:4996)
// 8���� �ؽ����̺�
// �����ּҹ� �˰��� (�浹o -> �����)

#define M 13

typedef struct
{
	int key;
	int proveCount;
}Bucket;

typedef struct
{
	Bucket A[M];
}HashType;

void init(HashType* H)
{
	for (int i = 0; i < M; i++) {
		H->A[i].key = 0;
		H->A[i].proveCount = 0;
	}
}

int isEmpty(HashType* H, int b)
{
	return H->A[b].key == 0;
}

int h(int k)
{
	return k % M;
}

int h2(int k)
{
	return 11 - (k % 11);  //11�� M(13)���� ���� �Ҽ��� ���� ū �Ҽ�
}

int getNextBucketLinear(int v, int i)
{
	return (v + i) % M;
}

int getNextBucketQuadratic(int v, int i)
{
	return (v + (i * i)) % M;
}

int getNextBucketDouble(int v, int i, int k)
{
	return (v + i * h2(k)) % M;
}

void insertItem(HashType* H, int k)
{
	int v = h(k);
	int i = 0;
	int count = 0; //������� �ڸ��� �����

	while (i < M) //M�� ��� ã�ƺ��� ������ �ڸ��� ���ٴ� ��
	{  //���縦 �����ߴ�.
		count++;
		//int b = getNextBucketLinear(v,i);
		int b = getNextBucketQuadratic(v, i);
		//int b = getNextBucketDouble(v, i, k);
		if (isEmpty(H, b))
		{
			H->A[b].key = k;
			H->A[b].proveCount = count;
			return;
		}
		else {
			i++;
		}
	}
}

void print(HashType* H)
{
	printf("Bucket  key  Prove\n");
	printf("===================\n");
	for (int i = 0; i < M; i++) {
		printf("H[%02d]:   %2d    %d\n", i, H->A[i].key, H->A[i].proveCount);
	}
	printf("\n");
}

int findElement(HashType* H, int k)
{
	int v = h(k);
	int i = 0;

	while (i < M)
	{

		//int b = getNextBucketLinear(v,i);
		int b = getNextBucketQuadratic(v, i);
		//int b = getNextBucketDouble(v, i, k);
		if (isEmpty(H, b))
		{
			return 0;
		}
		else if (H->A[b].key == k)
			return 1;
	}
	return 0;
}

int removeElement(HashType* H, int k)
{
	int v = h(k);
	int i = 0;

	while (i < M)
	{

		//int b = getNextBucketLinear(v,i);
		int b = getNextBucketQuadratic(v, i);
		//int b = getNextBucketDouble(v, i, k);
		if (isEmpty(H, b))
		{
			return 0;
		}
		else if (H->A[b].key == k)
		{
			H->A[b].key = 0;
			H->A[b].proveCount = 0;
			return 0;
		}
	}
	return 0;
}


int main(void)
{
	HashType* H;
	init(&H);

	insertItem(&H, 25); insertItem(&H, 13); insertItem(&H, 16);
	insertItem(&H, 15); insertItem(&H, 7); insertItem(&H, 28);
	insertItem(&H, 31); insertItem(&H, 20); insertItem(&H, 1);
	insertItem(&H, 38);
	print(&H);

	return 0;
}