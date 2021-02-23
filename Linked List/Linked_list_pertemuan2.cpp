#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct candy
{
	int price;
	char name[100];
	candy *next;
		
}*curr, *head, *tail;

void addBack(int price, char name[100])
{
	curr = (candy*)malloc(sizeof(candy));
	curr->price = price;
	strcpy(curr->name, name);
	
	if(head == NULL)
	{
		head = tail = curr;
	}
	else
	{
		tail->next = curr;
		tail = curr;
	}
	tail->next = NULL;
}

void addFirst()
{
	
	
	
}

void removeLast()
{
	if(head!=tail)
	{
		if(head!=NULL)
		{
			curr = head;
		}
		while(curr->next != tail)
		{
			curr = curr->next;
		}
		free(tail);
		tail = curr;
		tail->next = NULL;	
		}
	}else
	{
		free(head);
		head = tail = NULL;
	}

}

void removeFirst()
{
	if(head!=NULL)
	{
		curr = head;
		head = head->next;
		free(curr); 
	}
}
void viewAll()
{
	curr = head;
	while(curr!=NULL)
	{
		printf("%s %d\n", curr->name, curr->price);
		curr = curr->next;
	}
}
int main ()
{
	candy c1;
	c1.price=100;
	
	addBack(100, "lolipop");
	addBack(200, "sugus");
	addBack(150, "ball");
	addBack(170, "yupi");
	removeLast();
	removeLast();
	removeLast();
	removeLast();
	
	viewAll();
	
	return 0;
}
