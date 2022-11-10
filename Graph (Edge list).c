#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable:4996)

//간선 리스트 구조

typedef struct Vertex {  //정점
	char vName;
	struct Vertex* next;
}Vertex;

typedef struct Edge { //간선
	int weight;
	Vertex* v1, * v2;
	struct Edge* next;
}Edge;

typedef struct {  //그래프 
	Vertex* vHead;
	Edge* eHead;
}Graph;

void init(Graph* G)
{
	G->vHead = NULL;
	G->eHead = NULL;
}

void makeVertices(Graph* G, char vName)
{
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->next = NULL;

	Vertex* p = G->vHead;
	if (p == NULL)  //첫번째이면
		G->vHead = v;
	else
	{
		while (p->next != NULL)
			p = p->next;
		p->next = v;
	}
}

Vertex* findVertex(Graph* G, char vName) //이름으로 그래프에서 주소 찾기
{
	Vertex* p = G->vHead;
	while (p->vName != vName)
		p = p->next;
	return p;
}

void insertEdge(Graph* G, int w, char v1, char v2)
{
	Edge* e = (Edge*)malloc(sizeof(Edge));
	e->weight = w;
	e->v1 = findVertex(G, v1);
	e->v2 = findVertex(G, v2);
	e->next = NULL;

	Edge* q = G->eHead;
	if (q == NULL) //첫번째 노드
		G->eHead = e;
	else
	{
		while (q->next != NULL)
			q = q->next;
		q->next = e;
	}
}

void print(Graph* G)
{
	Edge* q = G->eHead;
	for (; q != NULL; q = q->next) {
		printf("(%c)---%d---(%c)\n", q->v1->vName, q->weight, q->v2->vName);
	}
	printf("\n");
}

void findAdj(Graph* G, char vName)
{
	Edge* q = G->eHead;
	Vertex* p = findVertex(G, vName);

	for (; q != NULL; q = q->next) {
		if (q->v1 == p)
			printf("(%c) ", q->v2->vName);
		else if (q->v2 == p)
			printf("(%c) ", q->v1->vName);
	}
	printf("\n");
}

int main(void) {

	Graph G;
	init(&G);

	makeVertices(&G, 'a'); makeVertices(&G, 'b');
	makeVertices(&G, 'c'); makeVertices(&G, 'd');
	makeVertices(&G, 'e'); makeVertices(&G, 'f');

	insertEdge(&G, 1, 'a', 'b'); insertEdge(&G, 1, 'a', 'c');
	insertEdge(&G, 1, 'a', 'd'); insertEdge(&G, 2, 'a', 'f');
	insertEdge(&G, 1, 'b', 'c'); insertEdge(&G, 4, 'c', 'e');
	insertEdge(&G, 4, 'e', 'e'); insertEdge(&G, 3, 'e', 'f');

	print(&G);

	printf("\n");

	findAdj(&G, 'b'); //b랑 연결된 정점 찾기

	return 0;
}