#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable:4996)

typedef struct TreeNode {
	int key;
	struct TreeNode* parent, * left, * right;
}TreeNode;

int isExternal(TreeNode* v)  //�� ���� �����ʿ� �ƹ��͵� ����.
{
	return(v->left == NULL && v->right == NULL); //����ִ���
}

TreeNode* treeSearch(TreeNode* v, int k)
{
	if (isExternal(v)) //�ܺγ������ Ȯ��
		return v;

	if (k == v->key)                      //�̹� �����ϴ� ���
		return v;
	else if (k < v->key)
		return treeSearch(v->left, k);    // v������ ������ ��������
	else
		return treeSearch(v->right, k);   //ũ�� ���������� ���� �ٽü�ġ
}

void expandExternal(TreeNode* w)  //�¿�� �� ��尡 �ִ°� external
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
	TreeNode* w = treeSearch(root, k); //w = ���� Ű���� �ִٸ� �־���� ��ġ

	if (!isExternal(w))       //���γ���̴� = �ȿ� �̹� Ű���� �ִ�.
		return;
	else {                    //�ܺγ���̴� = �ȿ� Ű���� ����.
		w->key = k;         //w(���� �ܺγ��)�� Ű�� �־��ֱ�
		expandExternal(w);    //w�� ���γ��� ��������� �ܺγ�� ������ֱ�
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

void reduceExternal(TreeNode* root, TreeNode* z)  //z�� �ܺγ��
{
	TreeNode* w = z->parent; //w�� �ܺγ���� �θ���
	TreeNode* g = w->parent; //g�� �ܺγ���� �θ��� �θ���
	TreeNode* zs = sibling(z); //zs = z�� ������� (w�� �ٸ� �ڽĳ��)
	zs->parent = g;//��������� �θ�� 2ĭ �ö󰡾��� (1ĭ �ö� �θ� ������ �Ŷ�)

	if (g == NULL) //g�� ��Ʈ�� ( = ������ w�� ��Ʈ����)
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

	while (w->left != NULL)   //w�� �����ʿ��� ���� ���� �� ã��
		w = w->left;
	return w; ���� 3:40 2022 - 10 - 15
}

int removeElement(TreeNode* root, int k)
{
	TreeNode* w, * z, * y;
	w = treeSearch(root, k); //w = ������ ���
	if (isExternal(w)) return -1; //w�� �ܺγ��� (=ã�°��� ����)

	z = w->left;  //z�� w�� ���ʳ��

	if (!isExternal(z)) //������ ���γ��, �� ���ʿ� ���� ������
		z = w->right;  //������ Ȯ���غ���

	if (isExternal(z)) //z�� �ܺγ���(=���� ����), �� w�� ������ �����
		reduceExternal(root, z);  //�ܺγ�常 �����ָ� �ȴ�.

	else {
		z = inOrderSucc(w);    //z�� w�� ����� ���� �ִ� ��� �ؿ� ���
		y = z->parent;         //y�� z�� �θ�(z�� ����� �� = y)
		w->key = y->key;       //w�� ���� y�� ������ ä���
		reduceExternal(root, z);  //z(�ܺγ��)�� �����
	}
	return k;
}

int main(void)
{
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->parent = root->left = root->right = NULL;  //��Ʈ�� �θ� ����

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