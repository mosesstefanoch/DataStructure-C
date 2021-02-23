#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

struct item{
	char name[50];
	int price;
	int qty;
	item *next, *prev;
}*head, *tail, *curr, *temp, *search;

void pMem(char names[], int prices, int qtys){
	curr = (item*)malloc(sizeof(item));
	strcpy(curr->name, names);
	curr->price = prices;
	curr->qty = qtys;
	curr->next = curr->prev = NULL;
}

void pushhead(char namep[], int pricep, int qtyp){
	pMem(namep, pricep, qtyp);
	if(head==NULL){
		head=tail=curr;
	}
	else{
		curr->next=head;
		head->prev=curr;
		head=curr;
	}
}

void pushtail(char namep[], int pricep, int qtyp){
	pMem(namep, pricep, qtyp);
	if(head==NULL){
		head=tail=curr;
	}
	else{
		tail->next=curr;
		curr->prev=tail;
		tail=curr;
	}
}

void pushmid(char namep[], int pricep, int qtyp){
	pMem(namep, pricep, qtyp);
	if(head==NULL){
		head=tail=curr;
	}
	else if(strcmp(curr->name, tail->name)>=0){
		pushtail(namep,pricep, qtyp);
	}
	else if(strcmp(curr->name, head->name)<0){
		pushhead(namep,pricep, qtyp);
	}
	else{
		temp=head;
		do{
			temp=temp->next;
		}while(strcmp(curr->name, temp->next->name)>0);
		curr->next=temp->next;
		temp->next->prev=curr;
		temp->next=curr;
		curr->prev=temp;
	}
}

void pophead(){
	if(head!=tail){
		curr=head;
		head=curr->next;
		free(curr);
		head->prev=NULL;
	}
	else{
		head = tail = NULL;
	}
}

void poptail(){
	curr=tail;
	tail=curr->prev;
	free(curr);
	tail->next=NULL;
}

void popsearch(){
	temp=head;
	if(head->qty==0) pophead();
	else if(tail->qty==0) poptail();
	else{
		do{
		temp=temp->next;
		}while(temp->qty!=0);
		curr=temp->prev;
		curr->next=temp->next;
		temp->next->prev=curr;
		free(temp);
	}
}

void view(){
	int z=1;
	printf("No.---------Name---------Price---------Quantity\n");
	curr=head;
	while(curr!=NULL){
		printf("%d---------%s----------Rp%d----------%d\n", z, curr->name, curr->price, curr->qty);
		curr=curr->next;
		z++;
	}
}

bool startsWith(char string[], char syarat[]){
	int len = strlen(syarat);
	for(int i = 0; i < len; i++){
		if(string[i] != syarat[i]) return false;
	}
	if(string[len] == NULL) return false;
	return true;
}

bool hkecil(char s[]){
	int len=strlen(s);
	for(int i=5;i<len;i++){
		if (s[i]<'a') return false;
	}
	return true;
}

void add(){
	char name[50];
	int price;
	int qty;
	do{
		printf("Input Item name [must start with 'Item ']: ");
		scanf("%[^\n]", name); getchar();
	}while(!startsWith(name,"Item ") || !hkecil(name));
	do{
		printf("Input Price [more than or equals 10000]: ");
		scanf("%d", &price);
	}while(price<10000);
	do{
		printf("Input Quantity [more than or equals 1]: ");
		scanf("%d", &qty);
	}while(qty<1);
	pushmid(name, price, qty);
}

item* find(char string[]){
	temp = head;
	while(temp){
		if(strcmp(string, temp->name)==0) return temp;
		temp=temp->next;
	}
	return NULL;
}

void sale(){
	char name[50];
	int qty;
	if(head==NULL) printf("No data");
	else{
		do{
			printf("Input Product Name : ");
			scanf("%[^\n]", name); getchar();
			search = find(name);
		}while(!search);
		
		do{
			printf("Input Product Quantity : ");
			scanf("%d", &qty); getchar();
		
		}while(qty<1 || qty>search->qty);
		search->qty -= qty;
		if(search->qty==0) popsearch();
	}
}

int main(){
	int input;
	do{
		system("cls");
		view();
		printf("Item Management\n");
		printf("1. Add Product\n");
		printf("2. Sale Product\n");
		printf("3. Exit\n");
		printf("Choice : \n");
		scanf("%d", &input); getchar();
		switch(input){
		case 1: add();break;
		case 2: sale();break;
		}
	}while(input!=3);
	return 0;
}
