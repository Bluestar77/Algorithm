#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)


typedef struct Edge {
	int v1, v2;
	int weight;
	struct Edge* next;
}Edge;

typedef struct Vertex {
	int vName;
	struct Vertex* next;
}Vertex;

typedef struct {
	Vertex* vHead;
	Edge* eHead;
	Edge** matrix;
}Graph;

void initGraph(Graph* G, int n)
{
	G->eHead = NULL;
	G->vHead = NULL;
	G->matrix = (Edge**)malloc(sizeof(Edge*) * n);
	for (int i = 0; i < n; i++) {
		G->matrix[i] = (Edge*)malloc(sizeof(Edge) * n);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			G->matrix[i][j].next = NULL;
		}
	}

}

void makeVertex(Graph* G, int vName)
{
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->next = NULL;

	Vertex* p = G->vHead;
	if (p == NULL)
		G->vHead = v;
	else {
		while (p->next != NULL)
			p = p->next;
		p->next = v;
	}

}


void insertEdge(Graph* G, int w, int v1, int v2)
{
	Edge* e = (Edge*)malloc(sizeof(Edge));
	e->weight = w;
	e->v1 = v1;
	e->v2 = v2;
	e->next = NULL;

	Edge* q = G->eHead;
	if (q == NULL)
		G->eHead = e;
	else
	{
		while (q->next != NULL)
			q = q->next;
		q->next = e;
	}

	G->matrix[v1 - 1][v2 - 1].next = e;
	G->matrix[v2 - 1][v1 - 1].next = e;

}

void printGraph(Graph* G)
{
	for (int i = 0; i < 6; i++) {
		printf("%d : ", i + 1);
		for (int j = 0; j < 6; j++) {
			if (G->matrix[i][j].next != NULL)
				printf("(%d-%d : %d) ", G->matrix[i][j].next->v1, G->matrix[i][j].next->v2, G->matrix[i][j].next->weight);
		}
		printf("\n");
	}
}

int main(void)
{
	Graph G;
	initGraph(&G, 6);

	for (int i = 1; i <= 6; i++) {
		makeVertex(&G, i);
	}

	insertEdge(&G, 1, 1, 2); insertEdge(&G, 1, 1, 3);
	insertEdge(&G, 1, 1, 4); insertEdge(&G, 2, 1, 6);
	insertEdge(&G, 1, 2, 3); insertEdge(&G, 4, 3, 5);
	insertEdge(&G, 4, 5, 5); insertEdge(&G, 3, 5, 6);

	printGraph(&G);

	return 0;
}