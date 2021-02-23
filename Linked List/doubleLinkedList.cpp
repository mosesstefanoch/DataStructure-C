#include <stdio.h>
#include <stdlib.h>

struct Data{
	int num;
	
	Data* next;
	Data* prev;
}*head, *tail;

Data* init(int num){
	Data* curr = (Data*)malloc(sizeof(Data));
	curr->num = num;
	curr->next = curr->prev = NULL;
	
	return curr;
}

void pushHead(Data* curr){
	if(!head) head = tail = curr;
	else{
		curr->next = head;
		head->prev = curr;
		head = curr;
	}
}

void pushTail(Data* curr){
	if(!head) head = tail = curr;
	else{
		tail->next = curr;
		curr->prev = tail;
		tail = curr;
	}
}

void pushPriority(Data *curr){
	if(!head)head = tail = curr;
	else if(curr->num > head->num) pushHead(curr);
	else if(curr->num < tail->num) pushTail(curr);
	else{
		Data* temp = head;
		while(temp->next->num > curr->num){
			temp = temp->next;	
		}
		curr->next = temp->next;
		curr->next->prev = curr;
		temp->next = curr;
		curr->prev = temp;
	}
}

void popHead(){
	if(!head)return;
	if(head == tail){
		free(head);
		head = NULL;
	}
	else{
		head = head->next;
		free(head->prev);
		head->prev = NULL;
	}
}

void popTail(){
	if(!head)return;
	if(head == tail){
		free(head);
		head = NULL;
	}
	else{
		tail = tail->prev;
		free(tail->next);
		tail->next = NULL;
	}	
}

void popSearch(int num){
	if(!head) return;
	
	if(head->num == num) popHead();
	else if(tail->num == num) popTail();
	else{
		Data* temp = head;
		while(temp->num != num && temp!=tail){
			temp = temp->next;
		}
		if(temp->num != num)return;
		temp->next->prev = temp->prev;
		temp->prev->next = temp->next;
		free(temp);
		temp = NULL;
	}
}

void view(){
	if(head == NULL)return;
	Data* temp = head;
	while(temp != NULL){
		printf("%d ", temp->num);
		temp = temp->next;
	}
}

int main(){
	pushPriority(init(5));
	pushPriority(init(2));
	pushPriority(init(3));
	pushPriority(init(4));
	
	popSearch(6);
	
	view();
	return 0;
}
