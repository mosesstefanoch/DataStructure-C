#include<stdio.h>
#include<stdlib.h>

struct tnode{
	int value;
	struct tnode *next;
}*head = NULL, *tail=NULL, *curr, *del;

void printData(){
	if(head==NULL) printf("No Data");
	else{
		curr = head; //memposisikan curr di tempat head
		while(curr){
			printf("%d ", curr->value);
			curr = curr->next;
		}
	}
	printf("\n");
}

void pushHead(int x){
	// buat node baru
	struct tnode *node = (struct tnode*) malloc (sizeof(struct tnode));
	//beri nilai pada node baru
	node->value = x;
	//node disambungkan dengan linked list yang ada
	node->next = head;
	//head pindah menunjuk ke node baru
	head = node;
	
	if(head->next==NULL) tail = head;
	
	printData();
}

void pushTail(int x){
	struct tnode *node = (struct tnode*) malloc(sizeof(struct tnode));
	node->value = x;
	node->next = NULL;
	
	if(head==NULL) pushHead(x);
	else{
		tail->next = node;
		tail = node;
	}
	
	printData();
}

void pushAfter(int x, int key){
	curr = head;
	while(curr && curr->value != key)curr = curr->next;
	
	if(curr != NULL){
		struct tnode *node = (struct tnode*) malloc(sizeof(struct tnode));
		node->value = x;
		
		node->next = curr->next;
		curr->next = node;
	}else{
		puts("Key tidak ditemukan");
	}
	
	printData();
}

void popHead(){
	if(head){
		if(head == tail){
			free(head);
			head = tail = NULL;
		}else{
			curr = head;
			head = head->next;
			free(curr);
		}
	}
	printData();
}

void popTail(){
	if(head){
		if(head == tail){
			popHead();
		}else{
			curr = head;
			while(curr->next && curr->next != tail){
				curr = curr->next;
			}
			free(tail);
			curr->next = NULL;
			tail = curr;
		}
	}
	printData();
}

void pop(int x){
	if(head){
		if(head->value==x) popHead();
		else if(tail->value == x) popTail();
		else{
			curr = head;
			while(curr->next && curr->next->value != x) curr = curr->next;
			if(curr->next){
				del = curr->next;
				curr->next = del->next;
				free(del);
			}
		}
	}
		
	printData();
}

void popAll(){
	while(head) popHead();
}

int main(){
	printData();
	//popHead();
	
	pushHead(10); //10
	//popHead();
	//popTail();
	pushHead(100); //100 10
	
	//popTail();
	pushHead(200); //200 100 10
	pushHead(300); //300 200 100 10
	
	//popTail();
	
	pushTail(20); //300 200 100 10 20
	pushTail(30); //300 200 100 10 20 30
	pushTail(40); //300 200 100 10 20 30 40
	pushTail(50); //300 200 100 10 20 30 40 50
	
	//popHead();
	//popHead();
	//popHead();
	//popHead();
	//popHead();
	
	pushHead(5); //5 300 200 100 10 20 30 40 50
	pushTail(15); //5 300 200 100 10 20 30 40 50 15
	
	pushAfter(500, 100); //5 300 200 100 500 10 20 30 40 50 15
	pushAfter(600, 15); //5 300 200 100 500 10 20 30 40 50 15 600
	pushAfter(700, 2); //5 300 200 100 500 10 20 30 40 50 15 600
	
	popAll();
	
	//pop(15);
	//pop(600);
	//pop(5);
	
	return 0;
}

