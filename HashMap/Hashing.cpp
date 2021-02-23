#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct Data{
	int n;
	struct Data *next, *prev;
};
struct Data *head[10], *tail[10];

int hashing(int n){
	return n%10;
}

struct Data* createNode(int n){
	struct Data *newNode = (struct Data*)malloc(sizeof(struct Data));
	newNode->n = n;
	newNode->next = NULL;
	newNode->prev = NULL;
	
	return newNode;
}

//void pushHead(struct Data* newNode, int hashing){
//	if(!head[hashing]){
//		head[hashing] = tail[hashing] = newNode;
//	}else{
//		head[hashing]->prev = newNode;
//		newNode->next = head[hashing];
//		head[hashing] = newNode;
//	}
//}

void pushTail(struct Data* newNode){
	int hashin = hashing(newNode->n);
	if(!head[hashin]){
		head[hashin] = tail[hashin] = newNode;
	}else{
		tail[hashin]->next = newNode;
		newNode->prev = tail[hashin];
		tail[hashin] = tail[hashin]->next;
	}
}

//void pushMid(struct Data* newNode){
//	if(!head){
//		head[hashing] = tail[hashing] = newNode;
//	}else if(newNode->n <= head->n){
//		pushHead(newNode);
//	}else if(newNode->n >= tail->n){
//		pushTail(newNode);
//	}else{
//		struct Data* curr = head;
//		while(curr->next->n < newNode->n){
//			if(curr->next == NULL) break;
//			curr = curr->next;
//		}
//		newNode->next = curr->next;
//		newNode->prev = curr;
//		curr->next = newNode;
//		newNode->next->prev = newNode;
//	}
//}

void printAll(){
	struct Data* curr = head[0];
	int idx = 0;
	for(int i = 0; i<10; i++){
		curr = head[i];
		while(curr){
			printf("%d   ", curr->n);
			curr = curr->next;
		}
		printf("\n");
	}
}

int main(){
	pushTail(createNode(12));
	pushTail(createNode(10));
	pushTail(createNode(11));
	pushTail(createNode(14));
	pushTail(createNode(16));
	pushTail(createNode(16));
	printAll();
	
	return 0;
}
