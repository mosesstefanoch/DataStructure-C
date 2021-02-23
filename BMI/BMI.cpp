#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Data{
	char name[50];
	char cat[50];
	double bmi;

	struct Data *next, *prev;

}*head, *tail, *curr, *temp;

struct Data* initNode(char name[], char cat[], double bmi)
{
	struct Data *node = (struct Data*)malloc(sizeof(struct Data));
	strcpy(node->name, name);
	strcpy(node->cat, cat);
	node->bmi = bmi;

	node->next = NULL;
	node->prev = NULL;

	return node;
}

void pushhead(char name[],char cat[],double bmi)
{
	if(!head)
	{
		head = tail = curr;
	}
	else
	{
		head->prev = curr;
		curr->next = head;
		head = curr;
	}
}

void pushtail(char name[],char cat[],double bmi)
{
	if(!head)
	{
		head = tail = curr;
	}
	else
	{
		tail->next = curr;
		curr->prev = tail;
		tail = tail->next;
	}
}

void pushmid(char name[],char cat[],double bmi)
{
	curr = initNode(name,cat,bmi);
	if(!head)
	{
		head = tail = curr;
	}
	else if(curr->bmi < head->bmi) pushhead(name,cat,bmi);
	else if(curr->bmi >= tail->bmi)	pushtail(name,cat,bmi);
	else
	{
		struct Data* temp = head;
		while(temp->next->bmi <= curr->bmi)
		{
			if(temp->next == NULL) break;
			temp = temp->next;
		}
		curr->next = temp->next;
		curr->prev = temp;
		temp->next = curr;
		curr->next->prev = curr;
	}
}

void pophead()
{
	if(head!=tail)
	{
		curr = head;
		head = curr->next;
		free(curr);
		head->prev = NULL;
	}
	else
	{
		free(head);
		head = tail = NULL;
	}
}

void poptail()
{
	if(head!=tail)
	{
		curr = tail;
		tail = tail->prev;
		free(curr);
		tail->next = NULL;
	}
	else
	{
		free(tail);
		head = tail = NULL;
	}
}

void popmid()
{
	temp = head;
	while(temp)
	{
		if(strcmp(temp->cat, "Normal")==0)
		{
			if(temp->prev == NULL) pophead();
			else if(temp->next == NULL) poptail();
			else
			{
				Data *del = temp;
				temp = temp->prev;
				temp->next = del->next;
				del->next->prev = temp;
				free(del);
				del->next = del->prev = NULL;
			}
		}
		temp = temp->next;
	}
}

void add()
{
	char name[50], cat[50];
	double weight;
	double height;
	double bmi;

	do{
		printf("Full name [2-20 Characters]: ");
		scanf("%[^\n]", name);
		getchar();
	}while(strlen(name) < 2 || strlen(name) > 20);

	do{
		printf("Weight [25.00 - 300.00 in Kilogram]: ");
		scanf("%lf", &weight);
		getchar();
	}while(weight < 25.00 || weight > 300.00);

	do{
		printf("Height [0.50 - 3.00 in Meter]: ");
		scanf("%lf", &height);
		getchar();
	}while(height < 0.50 || height > 3.00);

	bmi = weight / (height * height);

	if(bmi < 18.5)
	{
		strcpy(cat, "Underweight");
	}
	else if(bmi > 25)
	{
		strcpy(cat, "Overweight");
	}
	else
	{
		strcpy(cat, "Normal");
	}
	
	pushmid(name, cat, bmi);

	printf("Success Add New Data!");
	getchar();
}

void view()
{
	temp = head;
	if(head == NULL)
	{
		printf("No Data!\n");
	}
	else
	{
		printf("|\tName\t|\tBMI\t|\tCategory\t|\n");
		while(temp)
		{
			printf("| %13s | %13.2lf | %21s |\n", temp->name , temp->bmi, temp->cat);
			temp = temp->next;
		}
		printf("\n");
	}
}

void deletenormal()
{
	popmid();
}

void popall()
{
	while(head)
	{
		if(head != tail)
		{
			curr = head;
			head = curr->next;
			free(curr);
		}
		else
		{
			free(head);
			head = tail = NULL;
		}
	}
}

void cls()
{
	for(int i=0 ; i<30 ; i++)
	{
		puts("");
	}
}

int main ()
{
	int choose = 0;

	do{
		cls();
		printf("Body Mass Index\n");
		printf("================\n\n");
		view();
		printf("1. Add New Data\n");
		printf("2. Delete All Data in Normal Category\n");
		printf("3. Exit\n");
		printf(">>");

		scanf("%d", &choose);
		getchar();

	switch(choose)
	{
		case 1:
			add();
			break;

		case 2:
			deletenormal();
			break;
	}

	}while(choose != 3);

	popall();

	return 0;
}