#include <stdio.h>
#include<stdlib.h>
struct node{
	struct node *left,*right;
	int value;
}*root;
struct node *newNode(int value){
	struct node *root=(struct node*) malloc (sizeof(struct node));
	root->value=value;
	root->left = root->right = NULL;
	return root;
}
void add(struct node **root, int value){
	if(*root==NULL) *root=newNode(value);
	else if((*root)->value>value) add(&(*root)->left,value);
	else if((*root)->value<value) add(&(*root)->right,value);
	else printf("Exist");
}
struct node *remove(struct node *no,int value){
	if(root==NULL) printf("nodata");
	else if(no==NULL)  printf("nofound");
	else if(no->value>value){
		no->left=remove(no->left,value);
	}
	else if(no->value<value){
		no->right=remove(no->right,value);
	}
	else{
		if(no->left==NULL&&no->right==NULL){
			free(no);
			no=NULL;
		}
		else if( no->left==NULL){
			no->value=no->right->value;
			free(no->right);
			no->right=NULL;
		}
		else if( no->right==NULL){
			no->value=no->left->value;
			free(no->left);
			no->left=NULL;
		}
		else{
			struct node *tem = no->left;
			while(tem->right!=NULL){
					tem=tem->right;
			}
			no->value = tem->value;
			no->left=remove(no->left,tem->value);
		}
	}
}
void infix(struct node *root){
	if(root!=NULL){
		infix(root->left);
		printf("%d",root->value);
		infix(root->right);
	}
}
void ostfix(struct node *root){
	if(root!=NULL){
		ostfix(root->left);
		ostfix(root->right);
		printf("%d",root->value);
	}
}void refix(struct node *root){
	if(root!=NULL){
		printf("%d",root->value);
		refix(root->left);
		refix(root->right);
	}
}
void rint(){
	ostfix(root);
	refix(root);
	infix(root);
}
int main(){
	add(&root,10);
	remove(root,10);
	rint();
}
