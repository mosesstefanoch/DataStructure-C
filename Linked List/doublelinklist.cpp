#include<stdio.h>
#include<stdlib.h>
//doublelinkedlist
struct data{
	int value;
	struct data *next,*prev;
}*head,*tail,*curr;

void pushdepan(int x){
	curr=(struct data*)malloc(sizeof(struct data));
	curr->value=x;
	
	if (head==NULL){
		head=tail=curr;
		tail->next=NULL;
		head->prev=NULL;//
	}
	else{
		curr->next=head;
		head->prev=curr;//
		head=curr;
		head->prev=NULL;//
	}
}

void pushbelakang(int x){
	curr=(struct data*)malloc(sizeof(struct data));
	curr->value=x;
	
	if (head==NULL){
		head=tail=curr;
		tail->next=NULL;
		head->prev=NULL;//
	}
	else{
		tail->next=curr;
		curr->prev=tail;//
		tail=curr;
		tail->next=NULL;
		
	}
}

void view(){
	curr=head;
	while(curr!=NULL){
		printf("%d ",curr->value);
		curr=curr->next;
	}
}

void popdepan(){
	if (head!=NULL){
		curr=head;
		head=head->next;
		free(curr);
		head->prev=NULL;//
	}
}

void popbelakang(){
	if (head!=NULL){
		if (head==tail){
			head=tail=NULL;
		}
		else{
		tail=tail->prev;//
		free(tail->next);
		tail->next=NULL;	
		}	
	}
}

int main(){
	pushdepan(1);
	pushdepan(3);
	pushdepan(5);
	
	pushbelakang(12);
	pushbelakang(24);
	pushbelakang(36);
	
	popdepan();
	popdepan();
	popdepan();
	
	popbelakang();
	popbelakang();
	popbelakang();
	
	view();
	
	return 0;
}
