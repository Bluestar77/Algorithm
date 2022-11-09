#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable:4996)

typedef struct TreeNode {
	int key;
	struct TreeNode* parent, * left, * right;
}TreeNode;

int isExternal(TreeNode* v)  //내 왼쪽 오른쪽에 아무것도 없다.
{
	return(v->left == NULL && v->right == NULL); //비어있는지
}

TreeNode* treeSearch(TreeNode* v, int k)
{
	if (isExternal(v)) //외부노드인지 확인
		return v;

	if (k == v->key)                      //이미 존재하는 노드
		return v;
	else if (k < v->key)
		return treeSearch(v->left, k);    // v갑보다 작으면 왼쪽으로
	else
		return treeSearch(v->right, k);   //크면 오른쪽으로 가서 다시서치
}

void expandExternal(TreeNode* w)  //좌우로 빈 노드가 있는게 external
{
	TreeNode* L = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* R = (TreeNode*)malloc(sizeof(TreeNode));

	L->left = NULL;
	L->right = NULL;
	L->parent = w;

	R->left = NULL;
	R->right = NULL;
	R->parent = w;

	w->left = L;
	w->right = R;
}


void insertItem(TreeNode* root, int k)
{
	TreeNode* w = treeSearch(root, k); //w = 만약 키값이 있다면 있어야할 위치

	if (!isExternal(w))       //내부노드이다 = 안에 이미 키값이 있다.
		return;
	else {                    //외부노드이다 = 안에 키값이 없다.
		w->key = k;         //w(현재 외부노드)에 키값 넣어주기
		expandExternal(w);    //w를 내부노드로 만들기위해 외부노드 만들어주기
	}
}


void preOrder(TreeNode* root)
{
	if (isExternal(root))
		return;
	if (root != NULL)
	{
		printf("[%d] ", root->key);
		preOrder(root->left);
		preOrder(root->right);
	}
}

void inOrder(TreeNode* root)
{
	if (isExternal(root))
		return;
	if (root != NULL)
	{
		inOrder(root->left);
		printf("[%d] ", root->key);
		inOrder(root->right);
	}
}

TreeNode* sibling(TreeNode* z)
{
	if (z->parent->left == z) return z->parent->right;
	else return z->parent->left;
}

void reduceExternal(TreeNode* root, TreeNode* z)  //z는 외부노드
{
	TreeNode* w = z->parent; //w는 외부노드의 부모노드
	TreeNode* g = w->parent; //g는 외부노드의 부모의 부모노드
	TreeNode* zs = sibling(z); //zs = z의 형제노드 (w의 다른 자식노드)
	zs->parent = g;//형제노드의 부모는 2칸 올라가야함 (1칸 올라간 부모가 삭제될 거라서)

	if (g == NULL) //g가 루트면 ( = 삭제한 w가 루트였다)
		root = zs;
	else
		if (w == g->left)
			g->left = zs;
		else
			g->right = zs;
	free(z);
	free(w);

}

TreeNode* inOrderSucc(TreeNode* w)
{
	w = w->right;

	while (w->left != NULL)   //w의 오른쪽에서 가장 작은 값 찾기
		w = w->left;
	return w; 오후 3:40 2022 - 10 - 15
}

int removeElement(TreeNode* root, int k)
{
	TreeNode* w, * z, * y;
	w = treeSearch(root, k); //w = 삭제할 노드
	if (isExternal(w)) return -1; //w가 외부노드다 (=찾는값이 없다)

	z = w->left;  //z는 w의 왼쪽노드

	if (!isExternal(z)) //왼쪽이 내부노드, 즉 왼쪽에 값이 있으면
		z = w->right;  //오른쪽 확인해보기

	if (isExternal(z)) //z가 외부노드다(=값이 없다), 즉 w가 마지막 노드라면
		reduceExternal(root, z);  //외부노드만 지워주면 된다.

	else {
		z = inOrderSucc(w);    //z는 w를 대신할 값이 있는 노드 밑에 노드
		y = z->parent;         //y는 z의 부모(z를 대신할 값 = y)
		w->key = y->key;       //w의 값은 y의 값으로 채우고
		reduceExternal(root, z);  //z(외부노드)를 지운다
	}
	return k;
}

int main(void)
{
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->parent = root->left = root->right = NULL;  //루트만 부모가 없음

	insertItem(root, 9); insertItem(root, 2);
	insertItem(root, 15); insertItem(root, 1);
	insertItem(root, 7); insertItem(root, 11);
	insertItem(root, 5); insertItem(root, 8);
	insertItem(root, 3); insertItem(root, 4);

	preOrder(root);
	printf("\n");
	inOrder(root);
	printf("\n");

	int key;
	scanf("%d", &key);
	printf("[%d]is deleted.\n", removeElement(root, key));
	preOrder(root);
	printf("\n");

	return 0;
}