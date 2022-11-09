//사전 검색 알고리즘 : 이미 정렬된 데이터를 O(log(n))으로 찾기

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable:4996)

int FindElement(int* L, int left, int right, int key)
{
	int mid = (left + right) / 2;

	while (left <= right) {
		if (L[mid] == key) return mid;
		else if (L[mid] < key)
			return FindElement(L, mid + 1, right, key);
		else
			return FindElement(L, left, mid - 1, key);
	}
	return mid;
}

int main(void)
{
	int n, k, t;
	scanf("%d %d", &n, &k);
	int* L = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &L[i]);
	}
	t = FindElement(L, 0, n - 1, k);
	if (t == 0 && L[t] != k) printf("-1");
	else printf("%d", t);
}