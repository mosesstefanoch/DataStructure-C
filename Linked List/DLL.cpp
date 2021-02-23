#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct Data{
	int n;
	char name[100];
	struct Data *next, *prev;
};
struct Data *head = NULL, *tail = NULL;


struct Data* createNode(int n, char *name){
	struct Data *newNode = (struct Data*)malloc(sizeof(struct Data));
	newNode->n = n;
	strcpy(newNode->name, name);
	newNode->next = NULL;
	newNode->prev = NULL;
	
	return newNode;
}

void pushHead(struct Data* newNode){
	if(!head){
		head = tail = newNode;
	}else{
		head->prev = newNode;
		newNode->next = head;
		head = newNode;
	}
}

void pushTail(struct Data* newNode){
	if(!head){
		head = tail = newNode;
	}else{
		tail->next = newNode;
		newNode->prev = tail;
		tail = tail->next;
	}
}

void pushMid(struct Data* newNode){
	if(!head){
		head = tail = newNode;
	}else if(newNode->n <= head->n){
		pushHead(newNode);
	}else if(newNode->n >= tail->n){
		pushTail(newNode);
	}else{
		struct Data* curr = head;
		while(curr->next->n < newNode->n){
			if(curr->next == NULL) break;
			curr = curr->next;
		}
		newNode->next = curr->next;
		newNode->prev = curr;
		curr->next = newNode;
		newNode->next->prev = newNode;
	}
}

void printAll(){
	struct Data* curr = head;
	while(curr){
		printf("%d %s\n", curr->n, curr->name);
		curr = curr->next;
	}
}

int main(){
	pushMid(createNode(12, "asd"));
	pushMid(createNode(12, "asd"));
	pushMid(createNode(12, "asd"));
	pushMid(createNode(12, "asd"));
	pushMid(createNode(12, "asd"));
	pushMid(createNode(12, "asd"));
	printAll();
	
	return 0;
}
