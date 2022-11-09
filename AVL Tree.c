#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))

typedef struct AVLNode
{
	int key;
	struct AVLNode* left;
	struct AVLNode* right;
}AVLNode;

AVLNode* createNode(int key)
{
	AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
	node->key = key;
	node->left = node->right = NULL;
	return node;
}

int getHeight(AVLNode* node)
{
	int heght = 0;
	if (node != NULL)
		heght = 1 + max(getHeight(node->left), getHeight(node->right));

	return heght;
}

int getBalance(AVLNode* node)
{
	if (node == NULL)
		return 0;

	return getHeight(node->left) - getHeight(node->right);
}

AVLNode* rotateRight(AVLNode* p)
{
	AVLNode* c = p->left;
	p->left = c->right;
	c->right = p;
	return c;
}

AVLNode* rotateLeft(AVLNode* p)
{
	AVLNode* c = p->right;
	p->right = c->left;
	c->left = p;
	return c;
}


AVLNode* insert(AVLNode* node, int key)
{
	if (node == NULL)
		return createNode(key);

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else
		return node;

	int balance = getBalance(node);

	if (balance > 1 && key < node->left->key) // LL
		return rotateRight(node);

	if (balance > 1 && key > node->left->key) // LR
	{
		node->left = rotateLeft(node->left);
		return rotateRight(node);
	}

	if (balance < -1 && key < node->right->key) // RL
	{
		node->right = rotateRight(node->right);
		return rotateLeft(node);
	}

	if (balance < -1 && key > node->right->key) // RR
		return rotateLeft(node);

	return node;
}

void preOrder(AVLNode* root)
{
	if (root != NULL)
	{
		printf("[%d] ", root->key);
		preOrder(root->left);
		preOrder(root->right);
	}
}


int main()
{
	AVLNode* root = NULL;
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		root = insert(root, rand() % 100 + 1);
		preOrder(root);
		printf("\n");
	}

}


