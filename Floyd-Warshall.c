#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable:4996)

//Floyd-Warshall �˰���

#define N 5 //���� 5��
#define INF 1000   //����ġ ���� ū ������ ����

void print(int graph[N][N])
{
	printf("*********************\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (graph[i][j] == INF)
				printf("  * ");
			else
				printf("%3d ", graph[i][j]);
		}
		printf("\n");
	}
	printf("*********************\n");
}

void floyd(int graph[N][N])
{
	printf("Base Graph\n");
	print(graph);

	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (graph[i][k] + graph[k][j] < graph[i][j])
					graph[i][j] = graph[i][k] + graph[k][j];
			}
		}
		getchar();
		printf("k = %d\n", k);
		print(graph);
	}

}

int main(void)
{
	int graph[N][N] = {      //����x���� ��� (�� = ����ġ)
		{0, 1, INF, 1, 5},
		{9, 0, 3, 2, INF},
		{INF, INF, 0, 4, INF},
		{INF, INF, 2, 0, 3},
		{3, INF, INF, INF, 0}
	};

	floyd(graph);

	return 0;
}