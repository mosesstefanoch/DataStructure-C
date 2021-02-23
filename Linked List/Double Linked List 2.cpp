#include<stdio.h>
#include<stdlib.h>

struct tnode{
	int value;
	struct tnode *next, *prev;
}*head=NULL, *tail=NULL, *curr;

void print(){
	if(!head) printf("No Data");
	else{
		curr = head;
		while(curr){
			printf("%d ", curr->value);
			curr = curr->next;
		}
	}
	printf("\n");
}

void pushHead(int x){
	struct tnode *node = (struct tnode*) malloc (sizeof(struct tnode));
	node->value = x;
	node->next = node->prev = NULL;
	
	//belum ada data
	if(head==NULL){
		head = tail = node;
	}else{
		node->next = head;
		head->prev = node;
		head = node;
	}
	print();
}

void pushTail(int x){
	struct tnode *node = (struct tnode*) malloc (sizeof(struct tnode));
	node->value = x;
	node->next = node->prev = NULL;
	
	if(head==NULL){
		head = tail = node;
	}else{
		node->prev = tail;
		tail->next = node;
		tail = node;
	}
	print();
}

void pushAfter(int x, int key){
	struct tnode *node = (struct tnode*) malloc (sizeof(struct tnode));
	node->value = x;
	node->next = node->prev = NULL;
	
	if(tail->value == key) pushTail(x);
	else{
		curr = head;
		while(curr && curr->value != key){
			curr = curr->next;
		}
		
		if(curr){
			node->next = curr->next;
			node->prev = curr;
			curr->next->prev = node;
			curr->next = node;
		}
		print();
	}
}

void pushBefore(int x, int key){
	struct tnode *node = (struct tnode*) malloc (sizeof(struct tnode));
	node->value = x;
	node->next = node->prev = NULL;
	
	if(head->value == key) pushHead(x);
	else{
		curr = head;
		while(curr && curr->value != key){
			curr = curr->next;
		}
		
		if(curr){
			node->next = curr;
			node->prev = curr->prev;
			curr->prev->next = node;
			curr->prev = node;
		}
		print();
	}
}

void popHead(){
	if(head){
		if(head==tail){
			free(head);
			head = tail = NULL;
		}else{
			head = head->next;
			free(head->prev);
			head->prev = NULL;
		}
		print();
	}
}

void popTail(){
	if(head){
		if(head==tail){
			free(head);
			head = tail = NULL;
		}else{
			tail = tail->prev;
			free(tail->next);
			tail->next = NULL;
		}
		print();
	}
}

void pop(int key){
	if(head){
		if(head->value == key) popHead();
		else if(tail->value == key) popTail();
		else{
			curr = head;
			while(curr && curr->value != key){
				curr = curr->next;
			}
			
			if(curr){
				curr->next->prev = curr->prev;
				curr->prev->next = curr->next;
				free(curr);
			}
			print();
		}
	}
}

void popAll(){
	if(head) popHead();
}

int main(){
	print();
	pushHead(10);
	pushHead(20);
	pushTail(30);
	pushAfter(25, 20);
	pushAfter(50, 25);
	pushBefore(150, 25);
	pushBefore(1500, 250);
//	popHead();
//	popTail();
//	pop(25);
//	pop(100);
//	pop(150);
	popAll();	
	return 0;
}
