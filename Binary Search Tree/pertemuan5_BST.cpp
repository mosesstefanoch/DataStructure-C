#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct tree{
	int value;
	tree *left, *right, *parent;	
}*root;

tree *createNode(int value)
{
	tree *node = (tree*)malloc(sizeof(tree));
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	
	return node;
}

void push(tree *curr, int value)
{
	if(curr == NULL)
	{
		root = createNode(value);
	}
	else
	{
		if(value < curr->value)
		{
			if(curr->left != NULL)
			{
				push(curr->left, value);	
			}
			else
			{
				curr->left = createNode(value);
			}
		}
		else
		{
			if(curr->right != NULL)
			{
				push(curr->right, value);	
			}
			else
			{
				curr->right = createNode(value);
			}
		}
	}
}

void postorder(tree *curr)
{
/*	if(curr->left != NULL)
	{
		postorder(curr->left);
	}
	if(curr->right != NULL)
	{
		postorder(curr->right);
	}
	printf("%d ", curr->value);*/
	if(curr!=NULL)
	{
		postorder(curr->left);
		postorder(curr->right);
		printf("%d ", curr->value);	
	}
}

void inorder(tree *curr)
{
	if(curr!=NULL)
	{
		inorder(curr->left);
		printf("%d ", curr->value);
		inorder(curr->right);	
	}
}

void preorder(tree *curr)
{
	if(curr!=NULL)
	{
		printf("%d ", curr->value);
		preorder(curr->left);
		preorder(curr->right);	
	}
}

int main ()
{

	push(root,10);
	push(root,5);
	push(root,20);
	push(root,8);
	push(root,15);
	push(root,30);
	
	/*printf("root %d\n", root->value);
	printf("root left %d\n", root->left->value);
	printf("root left right %d\n", root->left->right->value);
	printf("root right %d\n", root->right->value);*/
	printf("Post order : ");
	postorder(root);
	
	printf("\nInorder : ");
	inorder(root);
	
	
	printf("\nPreorder : ");
	preorder(root);
	return 0;
}
