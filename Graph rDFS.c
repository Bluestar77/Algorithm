#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable:4996)

//그래프 순회
//깊이우선탐색 with 재귀호출 (rDFS)

#define N 10  // vertex 개수
#define FALSE 0   //방문안했으면 0
#define TRUE 1    //방문했으면 1

typedef struct IncidentEdge {
	char aName;
	struct IncidentEdge* next;
}IncidentEdge;

typedef struct Vertex {
	char vName;
	int isVisit;         //방문여부 추가
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

void rDFS(GraphType* G, char vName)  //재귀적인 깊이우선탐색
{
	Vertex* v = findVertex(G, vName);
	IncidentEdge* p;

	if (v->isVisit == FALSE)
	{
		v->isVisit = TRUE;
		printf("[%c] ", v->vName);
	}

	for (p = v->iHead; p != NULL; p = p->next)
	{
		v = findVertex(G, p->aName);
		if (v->isVisit == FALSE)
			rDFS(G, v->vName);
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

	rDFS(&G, 'e');

	return 0;
}