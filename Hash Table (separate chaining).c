#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable:4996)
// 8���� �ؽ����̺�
// �и������ �˰��� (���Ḯ��Ʈ, �浹X)

#define M 13

typedef struct HashNode
{
	int key;
	struct HashNode* next;
}HashNode;

void init(HashNode* H)  //�ؽ��迭 �ʱ�ȭ
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
	H[v].next = node;  //���� ���� �ְ� ù��°��
}

void print(HashNode* H)
{ //���� H[M]�迭�� ���� �ȿ����� ����Ʈ�� ����
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

int removeElement(HashNode* H, int k) //������ ���� ����
{
	int v = h(k);  //Ű�� �迭 �ѹ�(v)�� ã�´�
	int count = 0;
	HashNode* p = &H[v]; //�迭 �׸� ��ü�� ����Ŵ H[v]
	HashNode* q;

	while (p->next != NULL) //��Ŷ�� ������ �޷�������
	{
		if (p->next->key == k) //�����Ϸ��� ���̸�
		{
			count++;
			q = p->next;  //q�� �����Ұ� ����
			p->next = q->next;  //q�� ������ p�� ������ ����Ű���� (=q�پ�Ѱ� ����)
			free(q); //q����
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
	printf("%d���� %d find.\n\n", findElement(H, k), k);

	printf("\nInput Remove Key : ");
	scanf("%d", &k);
	printf("%d���� %d deleted.\n\n", removeElement(H, k), k);
	print(H);

	return 0;
}