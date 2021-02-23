#include<stdio.h>
#include<stdlib.h>

struct data {
	int value;
	int height;
	data *left, *right;
};

data *createNode(int value) {
	data *curr = (data*)malloc(sizeof(data));
	curr->value = value;
	curr->left = NULL;
	curr->right = NULL;
	return curr;
}

int max (int a, int b) {
	if(a > b) return a;
	else return b;
}

int getHeight(data *curr) {
	// jika null return 0, selain itu return heightnya
	if(curr == NULL) return 0;
	else return curr->height;
}

int getBalanceFactor(data *curr) {
	// selisih height anak kiri dan anak kanan 
	// (height anak kiri - height anak kanan)
	if(curr == NULL) return 0;
	return getHeight(curr->left) - getHeight(curr->right);
}

data *rightRotation(data *curr) {
	data *oldLeft = curr->left;
	data *oldLeftRight = oldLeft->right;
	
	oldLeft->right = curr;
	curr->left = oldLeftRight;
	
	curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
	oldLeft->height = max(getHeight(oldLeft->left), getHeight(oldLeft->right)) + 1;
	
	return oldLeft;
}

data *leftRotation(data *curr) {
	data *oldRight = curr->right;
	data *oldRightLeft = curr->right->left;
	
	oldRight->left = curr;
	curr->right = oldRightLeft;
	
	curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
	oldRight->height = max(getHeight(oldRight->left), getHeight(oldRight->right)) + 1;
	
	return oldRight;
}

data *insert(data *curr, int value) {
	if (curr == NULL) {
		return createNode(value);
	} 
	
	if ( value < curr->value ) {
		curr->left = insert(curr->left, value);
	} else {
		curr->right = insert(curr->right, value);
	}
	
	curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
	
	int balanceFactor = getBalanceFactor(curr);
	bool leftIsHigher = balanceFactor > 1;
	bool rightIsHigher = balanceFactor < -1;
	
	if ( leftIsHigher && value < curr->left->value ) {
		return rightRotation(curr);
	} 
	else if (leftIsHigher && value > curr->left->value ) {
		curr->left = leftRotation(curr->left);
		return rightRotation(curr);
	} 
	else if (rightIsHigher && value > curr->right->value) {
		return leftRotation(curr);
	} 
	else if (rightIsHigher && value < curr->right->value) {
		curr->right = rightRotation(curr->right);
		return leftRotation(curr);
	}
	
	return curr;
} 

void print(data *curr) {
	if (curr != NULL) {
		print(curr->left);
		printf("%d ", curr->value);
		print(curr->right);
	}
}

int main() {
	data *root = NULL;
	
	root = insert(root, 10);
	root = insert(root, 20);
	root = insert(root, 30);
	printf("root : %d\n\n", root->value);
	//root = insert(root, 5);
	
	print(root);
}
