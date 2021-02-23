#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct data
{
	char part[51];
	int qty;
	struct data *next, *prev;
}*head, *tail, *curr;

void clear()
{
	int i;
	for(i=0;i<25;i++) printf("\n");
}

void pushhead(char part[], int qty)
{
	curr = (struct data*)malloc(sizeof(struct data));

	strcpy(curr->part, part);
	curr->qty = qty;

	if(head==NULL)
	{
		head = tail = curr;
	}
	else
	{
		curr->next = head;
		head->prev = curr;
		head = curr;
	}
	head->prev = NULL;
	tail->next = NULL;
}

void pop()
{
	struct data *temp;

	if(head!=NULL)
	{
		if(curr == head)
		{
			head = head->next;
			free(curr);
			if(head != NULL)
			{
				head->prev = NULL;
			}
		}
		else if(curr == tail)
		{
			curr = tail;
			tail = tail->prev;
			free(curr);
			tail->next = NULL;
		}
		else
		{
			temp = head;
			while(temp->next != curr)
			{
				temp = temp->next;
			}
			curr->next->prev = curr->prev;
			temp->next = curr->next;
			free(curr);
		}
	}
}

void popall()
{
	while(head!=NULL)
	{
		curr=head;
		head=head->next;
		free(curr);
	}
}

void view()
{
	int i = 0;
	clear();
	printf("                      ORDER LIST \n\n");
	printf(" | No.  | Name of Parts                  | Quantity |\n");
	curr = head;
	while(curr)
	{
		i++;
		printf(" | %3d. | %-30s | %8d |\n", i, curr->part, curr->qty);
		curr = curr->next;
	}
	printf("\n");
}

void addorder()
{
	char part[51];
	int qty;
	printf("\n\n\n");
	do
	{
		printf(" Input Name of Motorcycle's Part [3..30]: ");
		scanf("%[^\n]", part);
		fflush(stdin);
	}while(strlen(part)<3 || strlen(part)>30);
	printf("\n");
	do
	{
		printf(" Input Quantity of The Motorcycle's Part [1..20]: ");
		scanf("%d", &qty);
		fflush(stdin);
	}while(qty<1 || qty>20);
	
	pushhead(part, qty);

	printf("\n\n\n --- Add New Order Success ---\n");
	getchar();
}

void deleteorder()
{
	int tot = 0;
	int pos;
	int i;
	if(head==NULL)
	{
		printf("\n\n\n --- There is No Order in The List ---\n");
	}
	else
	{
		view();
		curr = head;
		while(curr)
		{
			tot++;
			curr = curr->next;
		}
		printf("\n\n");
		do
		{
			printf(" Input Number of The Order [1..%d]: ", tot);
			scanf("%d", &pos);
			fflush(stdin);
		}while(pos<1 || pos>tot);

		curr = head;

		for(i=1;i<pos;i++)
		{
			curr = curr->next;
		}

		pop();

		printf("\n\n\n --- Take Order Success ---\n");
	}
	getchar();
	fflush(stdin);
}

void menu()
{
	printf("\n BLUE MOTORCYCLE PARTS");
	printf("\n .....................\n");
	printf("\n 1. View Order List");
	printf("\n 2. Add New Order");
	printf("\n 3. Take Order");
	printf("\n 4. Exit");
	printf("\n\n >> Input choice : ");
}

int main()
{
	int choice;
	do
	{
		clear();
		menu();
		scanf("%d", &choice);
		fflush(stdin);

		switch(choice)
		{
			case 1 : view();
					 getchar();
					 fflush(stdin);
					 break;
			case 2 : addorder();
					 break;
			case 3 : deleteorder();
					 break;
		}
	}while(choice!=4);
	popall();
	return 0;
}
