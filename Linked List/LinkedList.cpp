#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data{
	char nim[15];
	char nama[100];
	int nilai;
	struct data *next;
}*head,*tail,*curr;

void push_depan(char nim[],char nama[],int nilai){
	int search=-1;
	curr=head;
	
	while(curr!=NULL){
		if(strcmp(nim,curr->nim)==0){
			curr->nilai=nilai;
			search=0;
			return;
		}
		curr=curr->next;
	}
	
	if(search==-1){
		curr=(struct data*)malloc(sizeof(struct data));
		curr->nilai=nilai;
		strcpy(curr->nama,nama);
		strcpy(curr->nim,nim);
		
		if(head==NULL){
			head=tail=curr;
			tail->next=NULL;
		}
		else{
			curr->next=head;
			head=curr;
		}
	}
	
}

void view_data(){
	curr=head;
	while(curr!=NULL){
		printf("%s %s %d\n",curr->nim,curr->nama,curr->nilai);
		curr=curr->next;
	}
}

int main(){
	
	push_depan("12345","AAAAA",50);
	push_depan("12343","BBBBB",55);
	push_depan("13232","CCCCC",65);
	push_depan("12343","AAAAA",70);
	push_depan("13232","BBBBB",85);
	
	
	view_data();
	return 0;
}
