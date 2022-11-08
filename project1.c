#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable:4996)

typedef struct Graph {
	int** matrix;
	int num;
}Graph;


void init(Graph* g)
{
	for (int i = 0;i < g->num;i++) {
		for (int j = 0;j < g->num;j++) {
			g->matrix[i][j] = 0;
		}
	}
}

void print(Graph* g)
{
	for (int i = 0;i < g->num;i++) {
		printf("%d row : ", i+1);
		for (int j = 0;j < g->num;j++) {
			printf(" %d", g->matrix[i][j]);
		}
		printf("\n");
	}
}

void insertEdge(Graph* g, int v1, int v2, int w)
{
	if (v1 > g->num + 1 || v2 > g->num + 1 || v1 <= 0 || v2 <= 0) {
		return;
	}
	g->matrix[v1 - 1][v2 - 1] = w;
	g->matrix[v2 - 1][v1 - 1] = w;
}

void nodeprint(Graph* g, int n)
{
	if (n > g->num || n <= 0) {
		printf("-1\n");
		return;
	}
	for (int i = 0;i < g->num;i++) {
		if (g->matrix[n-1][i] > 0) printf(" %d %d", i+1, g->matrix[n-1][i]);
	}
	printf("\n");
}

void modify(Graph* g, int v1, int v2, int w)
{
	if (v1 > g->num + 1 || v2 > g->num + 1 || v1 <= 0 || v2 <= 0) {
		printf("-1\n");
		return;
	}

	g->matrix[v1 - 1][v2 - 1] = w;
	g->matrix[v2 - 1][v1 - 1] = w;

}

int main(void)
{
	Graph G;
	int i;
	int n = 6;
	
	G.matrix = (int**)malloc(sizeof(int*) * n);
	for (i = 0;i < n;i++) {
		G.matrix[i] = (int*)malloc(sizeof(int) * n);
	}
	G.num = n;

	init(&G);

	insertEdge(&G, 1, 2, 1); insertEdge(&G, 1, 3, 1);
	insertEdge(&G, 1, 4, 1); insertEdge(&G, 2, 3, 1);
	insertEdge(&G, 3, 5, 4); insertEdge(&G, 5, 5, 4);
	insertEdge(&G, 5, 6, 3); insertEdge(&G, 1, 6, 2);

	char ch;
	int t,v1,v2,w;
	while (1){
		scanf("%c", &ch);
		if (ch == 'a') {
			scanf("%d", &t);
			nodeprint(&G, t);
		}

		else if (ch == 'm') {
			scanf("%d %d %d", &v1, &v2, &w);
			modify(&G, v1, v2, w);
		}

		else if (ch == 'p') {
			print(&G);
			printf("\n");
		}

		else if (ch == 'q')
			break;
	}

}