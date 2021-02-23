#include <stdio.h>
#include <stdlib.h>

struct tree{
	int val;
	struct tree *left;
	struct tree *right;
}*root = NULL;

struct tree *createNode(struct tree *curr, int val){
	struct tree *node = (struct tree*)malloc(sizeof(tree));
	node->val = val;
	node->left = NULL;
	node->right = NULL;
	return node;
}

struct tree* insert(struct tree *curr, int val){
	if(curr == NULL){
		return createNode(curr, val);
	}else{
		if(val < curr->val)
			curr->left = insert(curr->left, val);
		else if(val > curr->val)
			curr->right = insert(curr->right, val);
		else if(val == curr->val){
			printf("Data already exists!\n");
			return curr;
		}
	}
	return node;
}

void preorder(struct tree *curr){
	if(curr != NULL){
		printf("%d\n", curr->val);
		preorder(curr->left);
		preorder(curr->right);
	}
}

struct tree *search(struct tree *curr, int val){
	if(curr != NULL){
		if(curr->val == val)
			return curr;
		else if(val < curr->val)
			return search(curr->left, val);
		else if(val > curr->val)
			return search(curr->right, val);
	}else{
		printf("%d not found!\n", val);
	}
	return node;
}

struct tree *getMaxVal(struct tree *curr){
	if(curr != NULL){
		if(curr->right != NULL)
			getMaxVal(curr->right);
		else
			return curr;
	}
	return node;
}

struct tree *getMinVal(struct tree *curr){
	if(curr != NULL){
		if(curr->left != NULL)
			getMinVal(curr->left);
		else
			return curr;
	}
	return node;
}

void popAll(struct tree *curr){
	if(curr != NULL){
		popAll(curr->left);
		popAll(curr->right);
		free(curr);
	}
}

struct tree *deleteNode(struct tree *curr, int val){
	if(curr != NULL){
		if(val < curr->val){
			curr->left = deleteNode(curr->left, val);
		}else if(val > curr->val){
			curr->right = deleteNode(curr->right, val);
		}else{
			//only one left child
			if(curr->left == NULL){ 
				struct tree *x = curr->right;
				free(curr);	
				return x;
			}else if(curr->right == NULL){
				struct tree *x = curr->left;
				free(curr);	
				return x;
			}else{ //two children
				if(curr->left != NULL){
					struct tree *max = getMaxVal(curr->left);
					curr->val = max->val;
					curr->left = deleteNode(curr->left, max->val);
				}else if(curr->right != NULL){
					struct tree *min = getMinVal(curr->right);
					curr->val = min->val;
					curr->right = deleteNode(curr->right, min->val);
				}
			}	
		}
	}else{
		printf("%d Not Found!\n", val);
		return NULL;
	}
	return node;
}

int main(){
	//preorder, inorder, postorder
	root = insert(root, 12);
	insert(root, 20);
	insert(root, 8);
	insert(root, 15);
	insert(root, 30);
	insert(root, 5);
	insert(root, 10);
	insert(root, 30);
	insert(root, 9);
	/*
	struct tree *temp = search(root, 13);
	if(temp != NULL)
		printf("%d found!\n", temp->val);
	*/
	//deleteNode(root, 12);
	preorder(root);
	popAll(root);
	getchar();
}
