#include<stdio.h>
#include<stdlib.h>

//tambahan doublelinkedlist
struct Data{
	int num;
	
	Data* next;
	Data* prev;
}*head,*tail,*curr;

Data* initial(int num){//bikin kotaknya dlu 
	Data* curr=(Data*)malloc(sizeof(Data));
	curr->num=num;
	curr->next=curr->prev=NULL;
	
	return curr;
}

void pushdepan(Data* curr){
	if (!head) head = tail = curr;
	else {
		curr->next=head;
		head->prev=curr;
		head=curr;
	}
}

void pushbelakang(Data* curr){
	if (!head) head = tail = curr;
	else {
		tail->next=curr;
		curr->prev=tail;
		tail=curr;
	}
}

void view(){
	if (head==NULL) return;
	Data* temp=head;
		while(temp!=NULL){
			printf("%d ",temp->num);
			temp=temp->next;
		}
}

void popdepan(){
	if(!head)return;
	if(head==tail){//kalo sama lgsg aja 
		free(head);
		head=NULL;
	}
	else{//buat data yg banyak
		head=head->next;
		head->prev=NULL;
	}
}

void popbelakang(){
	if(!head)return;
	if(head==tail){//kalo sama lgsg aja 
		free(head);
		head=NULL;
	}
	else{//buat data yg banyak
		tail=tail->prev;
		free(tail->next);
		tail->next=NULL;
	}
}

void pushPriority(Data* curr){//ascending //kalo mau descending tinggal ganti tanda nya aja 
	if(!head)head=tail=curr;
	else if(curr->num < head->num) pushdepan(curr);
	else if(curr->num > tail->num) pushbelakang(curr);
	else{
		Data* temp=head;
		while(temp->next->num < curr->num) {
			temp=temp->next;
		}
		curr->next= temp->next;
		curr->next->prev=curr;
		temp->next=curr;
		curr->prev=temp;
	}
}

void popsearch(int num){
	if(!head) return;
	
	if(head->num == num) popdepan();
	else if(tail->num == num) popbelakang();
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

int main (){
	
	//pushdepan(initial(3));
	//pushdepan(initial(4));
	
	//pushbelakang(initial(5));
	//pushbelakang(initial(6));
	
    //popdepan();//hapus dr yg urutan pertama dulu dari depan 
	//popdepan();

    //popbelakang();
  	//popbelakang();
  	
  	pushPriority(initial(2));
  	pushPriority(initial(1));
  	pushPriority(initial(4));
  	pushPriority(initial(3));
  	
  	popsearch(4);
  	
	view();
	
}
