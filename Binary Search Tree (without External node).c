#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct TreeNode
{
	element key;
	struct TreeNode* left, * right;
}TreeNode;

TreeNode* insertNode(TreeNode* root, element key)
{
	if (root == NULL)
	{
		TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
		node->key = key;
		node->left = node->right = NULL;
		return node;
	}

	if (key < root->key)
		root->left = insertNode(root->left, key);
	else if (key > root->key)
		root->right = insertNode(root->right, key);

	return root;
}

TreeNode* minValueNode(TreeNode* root)
{
	TreeNode* current = root;
	while (current->left != NULL)
		current = current->left;
	return current;
}

TreeNode* deleteNode(TreeNode* root, int key)
{
	if (root == NULL)
		return root;

	if (key < root->key)
		root->left = deleteNode(root->left, key);
	else if (key > root->key)
		root->right = deleteNode(root->right, key);
	else
	{
		if (root->left == NULL)
		{
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		else
		{
			TreeNode* temp = minValueNode(root->right);
			root->key = temp->key;
			root->right = deleteNode(root->right, temp->key);
		}
	}
	return root;
}

void preOrder(TreeNode* root)
{
	if (root)
	{
		printf("[%d] ", root->key);
		preOrder(root->left);
		preOrder(root->right);
	}
}

void inOrder(TreeNode* root)
{
	if (root)
	{
		inOrder(root->left);
		printf("[%d] ", root->key);
		inOrder(root->right);
	}
}

void postOrder(TreeNode* root)
{
	if (root)
	{
		postOrder(root->left);
		postOrder(root->right);
		printf("[%d] ", root->key);
	}
}

int main()
{
	TreeNode* root = NULL;

	root = insertNode(root, 35);
	root = insertNode(root, 68);
	root = insertNode(root, 99);
	root = insertNode(root, 18);
	root = insertNode(root, 7);
	root = insertNode(root, 3);
	root = insertNode(root, 12);
	root = insertNode(root, 26);
	root = insertNode(root, 22);
	root = insertNode(root, 30);

	preOrder(root); printf("\n");
	inOrder(root);  printf("\n");
	postOrder(root); printf("\n"); printf("\n");

	deleteNode(root, 18); preOrder(root); printf("\n");
}
