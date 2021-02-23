#include<stdio.h>
#include<stdlib.h>


struct tree {
	int value;
	tree *left, *right, *parent;
}*root;

tree *createNode(int value) {
	tree *node = (tree*)malloc(sizeof(tree));
	node->value = value;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}

tree *searchNode(tree *curr, int value) {
	
	if (curr == NULL) return NULL;
	
	if (value < curr->value) {
		return searchNode(curr->left, value);
	} else if (value > curr->value) {
		return searchNode(curr->right, value);
	} else {
		return curr;
	}
}

bool isLeaf (tree *curr) {
	if (curr->left == NULL && curr->right == NULL) {
		return true;
	} else {
		return false;
	}
	// return curr->left == NULL && curr->right == NULL;
}

tree *leftMost(tree *curr) { // dapetin anak kiri paling kanan
	curr = curr->left;
	while(curr->right != NULL) {
		curr = curr->right;
	}
	return curr;
}

void pop(tree *curr, int value) {
	tree * dNode = searchNode(curr, value);
	
	if (dNode == NULL ) {
		printf("Data %d not found", value);
	} else {
		if ( isLeaf(dNode)) { // keduanya null
			// check isRightChild
			if ( dNode->parent->right == dNode ) {
				dNode->parent->right = NULL;
			} else {
				dNode->parent->left = NULL;
			}
			free(dNode);
		} else if (dNode->right!=NULL && dNode->left!=NULL) { // dua2 null
			// 
			tree *sub = leftMost(dNode);
			dNode->value = sub->value;
			pop(sub, sub->value);
			
		} else {// salah satu childnya null
			
			// cari tau child nya di left atau di right
			tree *child;
			if (dNode->right!=NULL) {
				child = dNode->right;
			} else {
				child = dNode->left;
			}
			
			// sambung child parent ke dNode parent
			
			child->parent = dNode->parent;
			
			// connect parent ke child
			if ( dNode->parent->right == dNode ) {
				dNode->parent->right = child;
			} else {
				dNode->parent->left = child;
			}
			free(dNode);
		}
	}
}

void push(tree *curr, int value) {
	if (curr == NULL) {
		root = createNode(value);
	} else {
		if (value < curr->value) {
			if (curr->left != NULL) {
				push(curr->left, value);
			} else {
				curr->left = createNode(value);
				curr->left->parent = curr;
			}
		
		} else {
			if (curr->right != NULL) {
				push(curr->right, value);
			} else {
				curr->right = createNode(value);
				curr->right->parent = curr;
			}
		}
	}
}

/*void push(tree *curr, int value) {
	if (curr == NULL) {
		curr = createNode(value);
	} else {
		if (value < curr->value) {
			push(curr->left, value);
		
		} else {
			push(curr->right, value);
		}
	}
}*/

void inorder(tree *curr) {
	/*if (curr->left != NULL) {
		postorder(curr->left);
	} 
	if (curr->right != NULL) {
		postorder(curr->right);
	}
	printf(" %d ", curr->value);*/
	
	if (curr!=NULL) {
		inorder(curr->left);
		printf(" %d ", curr->value);
		inorder(curr->right);
	}
}


int main() {
	
	push(root, 10);
	push(root, 5);
	push(root, 20);
	push(root, 8);
	push(root, 15);
	push(root, 30);
	
	pop(root, 30);
	
	inorder(root);
	
	/*
	printf("\nroot %d", root->value); //10
	printf("\nroot left %d", root->left->value); //5
	printf("\nroot left right %d", root->left->right->parent->value); //8
	printf("\nroot right %d", root->right->value); //20
	printf("\n postorder");
	*/
	
	//tree *test = searchNode(root, 8);
	//printf("\n test %d", test->parent->value);
	
}



