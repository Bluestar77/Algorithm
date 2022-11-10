#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable:4996)

//인접 리스트 구조


typedef struct Edge { //정점
	int weight;
	char v1, v2;
	struct Edge* next;
}Edge;

typedef struct IncidentEdge {
	char adjVertex;
	Edge* e;
	struct IncidentEdge* next;
}IncidentEdge;

typedef struct Vertex {  //간선
	char vName;
	IncidentEdge* iHead;
	struct Vertex* next;
}Vertex;


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
	v->iHead = NULL;
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

void insertincidentEdge(Vertex* v, char av, Edge* e)
{
	IncidentEdge* i = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	i->adjVertex = av;
	i->e = e;
	i->next = NULL;

	IncidentEdge* r = v->iHead;
	if (r == NULL)
		v->iHead = i;
	else
	{
		while (r->next != NULL)
			r = r->next;
		r->next = i;
	}
}

void insertEdge(Graph* G, int w, char v1, char v2)
{
	Edge* e = (Edge*)malloc(sizeof(Edge));
	e->weight = w;
	e->v1 = v1;  //간선과 다르게 이름 자체로 받음
	e->v2 = v2;
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

	Vertex* v = findVertex(G, v1);
	insertincidentEdge(v, v2, e);
	v = findVertex(G, v2);
	insertincidentEdge(v, v1, e);
}

void print(Graph* G)
{
	Vertex* p = G->vHead;
	IncidentEdge* r;

	for (; p != NULL; p = p->next)
	{
		printf("[%c] : ", p->vName);
		for (r = p->iHead; r != NULL; r = r->next)
			printf("(%c - %d) ", r->adjVertex, r->e->weight);
		printf("\n");
	}
	printf("\n");
}

void modifyweight(Graph* G, char v1, char v2, int w)  //가중치 변경
{
	Vertex* v = findVertex(G, v1);
	IncidentEdge* r = v->iHead;

	while (r)
	{
		if (r->adjVertex == v2) {
			r->e->weight = w;
			break;
		}
		else
			r = r->next;
	}
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

	modifyweight(&G, 'a', 'b', 3);

	print(&G);

	return 0;
}