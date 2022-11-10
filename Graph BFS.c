#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable:4996)

//�׷��� ��ȸ
//�ʺ�켱Ž��(BFS)

#define N 10  //vertex ����
#define FALSE 0   //�湮�������� 0
#define TRUE 1    //�湮������ 1

typedef struct IncidentEdge {
	char aName;
	struct IncidentEdge* next;
}IncidentEdge;

typedef struct Vertex {
	char vName;
	int isVisit;         //�湮���� �߰�
	IncidentEdge* iHead;
	struct Vertex* next;
}Vertex;

typedef struct {
	Vertex* vHead;
}GraphType;

void initGraph(GraphType* G)
{
	G->vHead = NULL;
}

void makeVertex(GraphType* G, char vName)
{
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->isVisit = FALSE;
	v->iHead = NULL;
	v->next = NULL;

	Vertex* p = G->vHead;
	if (p == NULL)
		G->vHead = v;
	else
	{
		while (p->next != NULL)
			p = p->next;
		p->next = v;
	}
}

void makeIncidentEdge(Vertex* v, char vName)
{
	IncidentEdge* p = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	p->aName = vName;
	p->next = NULL;

	IncidentEdge* q = v->iHead;
	if (q == NULL)
		v->iHead = p;
	else {
		while (q->next != NULL)
			q = q->next;
		q->next = p;
	}
}

Vertex* findVertex(GraphType* G, char vName)
{
	Vertex* p = G->vHead;
	while (p->vName != vName)
		p = p->next;
	return p;
}

void insertEdge(GraphType* G, char v1, char v2)
{
	Vertex* v = findVertex(G, v1);
	makeIncidentEdge(v, v2);

	v = findVertex(G, v2);
	makeIncidentEdge(v, v1);

}


typedef struct {       //�ʺ�켱Ž���� ���� ť ����
	Vertex* queue[N];
	int front, rear;
}QueueType;

void initQueue(QueueType* Q)
{
	Q->front = 0;
	Q->rear = 0;
}

int isQueueEmpty(QueueType* Q)   //����ִ��� Ȯ��
{
	return Q->rear == Q->front;
}

void enqueue(QueueType* Q, Vertex* v)  //����
{
	Q->rear = (Q->rear + 1) % N;
	Q->queue[Q->rear] = v;
}

Vertex* dequeue(QueueType* Q)          //����
{
	Q->front = (Q->front + 1) % N;
	return Q->queue[Q->front];
}

void BFS(GraphType* G, char vName)     //�ʺ�켱Ž��
{
	Vertex* v = findVertex(G, vName);
	IncidentEdge* p;

	QueueType Q;
	initQueue(&Q);

	v->isVisit = TRUE;
	printf("[%c] : ", v->vName);
	enqueue(&Q, v);

	while (!isQueueEmpty(&Q))
	{
		v = dequeue(&Q);
		for (p = v->iHead; p != NULL; p = p->next)
		{
			v = findVertex(G, p->aName);
			if (v->isVisit == FALSE)
			{
				v->isVisit = TRUE;
				printf("[%c] ", v->vName);
				enqueue(&Q, v);
			}
		}
	}

}


void printGraph(GraphType* G)
{
	Vertex* p = G->vHead;
	IncidentEdge* q;

	for (; p != NULL; p = p->next)
	{
		printf("[%c] : ", p->vName);
		for (q = p->iHead; q != NULL; q = q->next) {
			printf("[%c] ", q->aName);
		}
		printf("\n");
	}
	printf("\n");
}

int main(void) {

	GraphType G;
	initGraph(&G);

	makeVertex(&G, 'a'); makeVertex(&G, 'b');
	makeVertex(&G, 'c'); makeVertex(&G, 'd');
	makeVertex(&G, 'e'); makeVertex(&G, 'f');
	makeVertex(&G, 'g');

	insertEdge(&G, 'a', 'b'); insertEdge(&G, 'a', 'f');
	insertEdge(&G, 'b', 'c'); insertEdge(&G, 'b', 'g');
	insertEdge(&G, 'c', 'd'); insertEdge(&G, 'd', 'g');
	insertEdge(&G, 'd', 'e'); insertEdge(&G, 'e', 'g');
	insertEdge(&G, 'e', 'f');

	printGraph(&G);

	BFS(&G, 'g');

	return 0;
}