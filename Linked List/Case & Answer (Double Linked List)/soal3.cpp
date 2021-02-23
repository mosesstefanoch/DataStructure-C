#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct song{
	char name[100];
	song *next, *prev;

}*head, *tail, *curr, *cursor;

void node(char name[])
{
	curr = (song*)malloc(sizeof(song));
	strcpy(curr->name, name);
	curr->next = curr->prev = NULL;
}

void pushtail(char name[])
{
	node(name);
	if(head==NULL)
	{
		head=tail=curr;
	}
	else
	{
		tail->next = curr;
		curr->prev = tail;
		tail=curr;
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
		head = tail = NULL;
	}
}

void poptail()
{
	curr = tail;
	tail = curr->prev;
	free(curr);
	tail->next = NULL;
}

void popcursor()
{
	if(cursor->prev == NULL) pophead();
	else if(cursor->next == NULL) poptail();
	else
	{
		curr = cursor->prev;
		curr->next = cursor->next;
		cursor->next->prev = curr;
		free(cursor);
	}
	cursor = head;
}

void naik()
{
	if(cursor->prev == NULL)
	{
		printf("Already at the top of the list");
	}
	else
	{
		cursor=cursor->prev;
	}
}

void turun()
{
	if(cursor->next == NULL)
	{
		printf("Already at the end of the list");
	}
	else
	{
		cursor = cursor->next;
	}
}

void view()
{
	int z = 1;
	printf("No             Song Title\n");
	curr = head;
	while(curr!=NULL)
	{
		if(curr==cursor)
		{
			printf("%d.        ->%s\n", z, curr->name);
			curr = curr->next;
		}
		else
		{
			printf("%d.           %s\n", z, curr->name);
			curr = curr->next;
		}
		z++;
	}
	printf("\n\n");
}


void cls()
{
	for(int i = 0 ; i<30 ; i++)
	{
		puts("");
	}
}

int main()
{
	int choose;

	pushtail((char*)"Summer Song");
	pushtail((char*)"Goodbye Days");
	pushtail((char*)"Umareyuku Monotachi e");
	pushtail((char*)"Candle Light");
	pushtail((char*)"Especially For You");
	pushtail((char*)"Never Say Never");
	pushtail((char*)"When You Love Someone");
	cursor=head;

	do{
		cls();
		view();
		printf("Menu :\n");
		printf("1. Move Cursor Up\n");
		printf("2. Move Cursor Down\n");
		printf("3. Delete this song\n");
		printf("4. Exit\n");
		printf("Input : ");
		scanf("%d", &choose);

		switch(choose)
		{
			case 1 :
				naik();
				break;

			case 2 :
				turun();
				break;

			case 3 :
				popcursor();
				break;
		}


	}while(choose!=4);


	return 0;
}