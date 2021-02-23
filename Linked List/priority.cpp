#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct data{
	char value[100];
	char prio[10];
	int prioo;
	struct data *next,*prev;
}*head,*tail,*curr,*temp;

void push(char x[],char y[]){
	curr = (struct data*) malloc(sizeof(struct data));
	strcpy(curr->value,x);
	strcpy(curr->prio,y);
	
	if (strcmpi(y,"VIP")==0) curr->prioo=1;
	else if(strcmpi(y,"Gold")==0) curr->prioo=2;
	else if(strcmpi(y,"Silver")==0) curr->prioo=3;
	
	if(head == NULL){
		head  = tail = curr;
		tail->next = NULL;
	}else if(tail->prioo <= curr->prioo){
		tail->next = curr;
		curr->prev = tail;
		tail = curr;
		tail->next = NULL;
	}else if(head->prioo > curr->prioo){
		curr->next = head;
		head->prev = curr;
		head = curr;
		head->prev = NULL;
	}else{
		temp = head;
		while(temp&&curr->prioo >= temp->next->prioo){
			temp = temp->next;
		}
		curr->prev = temp;
		curr->next = temp->next;
		temp->next->prev = curr;
		temp->next = curr;
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

void view_data(){
	curr = head;
	while(curr){
		printf("%s %s\n",curr->value,curr->prio);
		curr = curr->next;
	}
}

int main(){
	
	push("Moses6","Silver");
	push("Ricky1","Gold");
	push("Ricky2","VIP");
	push("Ricky3","VIP");
	push("Ricky4","Gold");
	push("Moses5","Silver");
	
//	popdepan();
	
	view_data();
	return 0;
}
