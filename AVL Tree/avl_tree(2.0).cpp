#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Data{
	int key;
	int height;
	Data *left, *right;
}*root, *curr;

int arr[100],flag=0, kthnum, num,flag1=0;

Data *createNode(int key)
{
	curr = (Data*)malloc(sizeof(Data));
	curr->key = key;
	curr->height = 1;
	curr->left = curr->right = NULL;
	return curr;
}

int getHeight(Data *node)
{
	if(!node) return 0;
	return node->height;
}

int updateHeight(Data *node)
{
	int childHeight = (getHeight(node->left) > getHeight(node->right)) ? getHeight(node->left) : getHeight(node->right);
	return childHeight + 1;
}

int getBalance(Data *node)
{
	return getHeight(node->left) - getHeight(node->right);
}

Data *leftRotate(Data *node)
{
	Data *x = node->right;
	Data *y = x->left;
	
	node->right = y;
	x->left = root;
	
	node->height = updateHeight(node);
	x->height = updateHeight(node);
	
	return x;
}

Data *rightRotate(Data *node)
{
	Data *x = node->left;
	Data *y = x->right;
	
	node->left = y;
	x->right = root;
	
	node->height = updateHeight(node);
	x->height = updateHeight(node);
	
	return x;
}

Data *push(Data *node, int key)
{
	if(!node) return createNode(key);
	
	if(key < node->key)
	{
		node->left = push(node->left, key);
	}
	else if(key > node->key)
	{
		node->right = push(node->right, key);
	}
	
	node->height = updateHeight(node);
	
	int balance = getBalance(node);
	
	if(balance > 1)
	{
		if(getBalance(node) < 0)
		{
			node->left = leftRotate(node->left);
		}
		node = rightRotate(node);
	}
	else if(balance < -1)
	{
		if(getBalance(node) > 0)
		{
			node->right = rightRotate(node->right);
		}
		node = leftRotate(node);
	}
	
	return node;
}

Data *preDeccessor(Data *node)
{
	while(node->right)
	{
		node = node->right;
	}
	return node;
}

Data *Delete(Data *node, int key)
{
	if(!node) return NULL;
	
	if(key < node->key)
	{
		node->left = Delete(node->left, key);
	}
	else if(key > node->key)
	{
		node->right = Delete(node->right, key);
	}
	else
	{
		if(!node->left && !node->right)
		{
			free(node);
			if(node == root)
			{
				root = NULL;
			}
			return NULL;
		}
		else if(node->left == NULL)
		{
			Data *temp = node->right;
			free(node);
			if(node == root)
				root = temp;
			return temp;
		}
		else if(node->right == NULL)
		{
			Data *temp = node->left;
			free(node);
			if(node == root)
				root = temp;
			return temp;
		}
		else
		{
			Data *temp = preDeccessor(node->left);
			node->key = temp->key;
			node->left = Delete(node->left, temp->key);
		}
	}
	
	node->height = updateHeight(node);
	
	int balance = getBalance(node);
	
	if(balance > 1)
	{
		if(getBalance(node) > 0)
		{
			node->left = leftRotate(node->left);
		}
		node = rightRotate(node);
	}
	else if(balance < -1)
	{
		if(getBalance(node) > 0)
		{
			node->right = rightRotate(node->right);
		}
		node = leftRotate(node);
	}
	
	return node;
}

void inOrder(Data *node)
{		
	if(node)
	{
		inOrder(node->left);
		arr[flag1++]= node->key;
		inOrder(node->right);	
	}
}

Data *popAll(Data *node)
{
	if(node)
	{
		popAll(node->left);
		popAll(node->right);
		free(node);
	}
	root = NULL;
}


int main()
{
	char choice;
	int element;
	scanf("%d", &element);
	getchar();
	for(int i=0;i<element;i++)
	{
		scanf("%c %d", &choice, &num);
		getchar();
	switch(choice)
	{
		case 'i':
		{
			root = push(root, num);
			flag++;
			num=0;
			break;
		}
	case 'd':
		{
			Delete(root, num);
			flag--;
			num=0;
			break;
		}
	case 'k':
		{
			kthnum = num;
			inOrder(root);
			if(kthnum>flag)
			{
				printf("Invalid \n");
			}
			else
			{
				printf("%d \n",arr[kthnum-1]);
			}
				
			num=0;
			break;
		}
		
	case 'c':
		inOrder(root);
		int jumlahkurang=0;
		for(int i=0;i<flag;i++)
		{
			if(arr[i]<num)
			{
				jumlahkurang++;
			}
			else
			{
				break;
			}
		}
		printf("%d\n", jumlahkurang);
		
		break;
	  }
	  
	}
	
	return 0;
}
