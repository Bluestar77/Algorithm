#include <stdio.h>
#include <stdlib.h>

//위상연결 알고리즘
//자신한테 들어오는 개수가 적은 것 부터 출력하는 방법
//자신한테 들어오는 개수가 0개인 것부터 큐에 넣고 넣은 정점이 가르키는 정점들의
//개수를 하나씩 지우고 다시 돌린다.

#define SIZE 10

typedef struct
{
	char elem[SIZE];
	int front, rear;
}QueueType;

typedef struct IncidentEdge
{
	char aName;
	struct IncidentEdge* next;
}IncidentEdge;

typedef struct Vertex
{
	char vName;
	IncidentEdge* iHead;
	struct Vertex* next;
}Vertex;

typedef struct
{
	Vertex* vHead;
	int vCount;
}Graph;

void initQueue(QueueType* Q)
{
	Q->front = Q->rear = 0;
}

void init(Graph* G)
{
	G->vHead = NULL;
	G->vCount = 0;
}

int isEmpty(QueueType* Q)
{
	return Q->rear == Q->front;
}

int isFull(QueueType* Q)
{
	return (Q->rear + 1) % SIZE == Q->front;
}

void enqueue(QueueType* Q, char vName)
{
	if (isFull(Q))
	{
		printf("FULL\n");
		return;
	}
	Q->rear = (Q->rear + 1) % SIZE;
	Q->elem[Q->rear] = vName;
}

char dequeue(QueueType* Q)
{
	if (isEmpty(Q))
	{
		printf("EMPTY\n");
		return 0;
	}
	Q->front = (Q->front + 1) % SIZE;
	return Q->elem[Q->front];
}

void makeVertex(Graph* G, char vName)
{
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->iHead = NULL;
	v->next = NULL;
	G->vCount++;

	Vertex* q = G->vHead;
	if (q == NULL)
		G->vHead = v;
	else
	{
		while (q->next != NULL)
			q = q->next;
		q->next = v;
	}
}

void makeIncidentEdge(Vertex* v, char aName)
{
	IncidentEdge* p = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	p->aName = aName;
	p->next = NULL;

	IncidentEdge* q = v->iHead;
	if (q == NULL)
		v->iHead = p;
	else
	{
		while (q->next != NULL)
			q = q->next;
		q->next = p;
	}
}

Vertex* findVertex(Graph* G, char vName)
{
	Vertex* p = G->vHead;
	while (p->vName != vName)
		p = p->next;
	return p;
}

void insertEdge(Graph* G, char v1, char v2)
{
	Vertex* v = findVertex(G, v1);
	makeIncidentEdge(v, v2);          //하나만 연결 (방향그래프)
}

void print(Graph* G)
{
	Vertex* p = G->vHead;
	IncidentEdge* q;
	for (; p != NULL; p = p->next)
	{
		printf("(%c) : ", p->vName);
		for (q = p->iHead; q != NULL; q = q->next)
			printf("(%c) ", q->aName);
		printf("\n");
	}
	printf("\n");
}

void inDegree(Graph* G, int in[])
{

	Vertex* p = G->vHead;
	IncidentEdge* q;

	for (; p != NULL; p = p->next) {
		for (q = p->iHead; q != NULL; q = q->next) {
			in[q->aName - 97]++;
		}
	}
}

void topologicalSort(Graph* G, int in[])
{
	QueueType Q;
	initQueue(&Q);

	Vertex* p;
	IncidentEdge* q;

	inDegree(G, in);

	for (int i = 0; i < G->vCount; i++) {
		if (in[i] == 0)
			enqueue(&Q, i + 97);
	}

	while (!isEmpty(&Q))
	{
		char vName = dequeue(&Q);
		printf("[%c] ", vName);
		p = findVertex(G, vName);
		q = p->iHead;

		while (q != NULL)
		{
			in[q->aName - 97]--;
			if (in[q->aName - 97] == 0)
				enqueue(&Q, q->aName);
			q = q->next;
		}
	}

}

int main()
{
	Graph G;
	init(&G);

	makeVertex(&G, 'a'); makeVertex(&G, 'b'); makeVertex(&G, 'c');
	makeVertex(&G, 'd'); makeVertex(&G, 'e'); makeVertex(&G, 'f');
	insertEdge(&G, 'a', 'b'); insertEdge(&G, 'a', 'e');
	insertEdge(&G, 'b', 'c'); insertEdge(&G, 'd', 'e');
	insertEdge(&G, 'e', 'b'); insertEdge(&G, 'e', 'c');
	insertEdge(&G, 'e', 'f'); insertEdge(&G, 'f', 'c');
	print(&G);

	int in[10] = { 0 };

	topologicalSort(&G, in);

}
