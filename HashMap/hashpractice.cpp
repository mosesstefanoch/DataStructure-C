#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Data{
	int value;

	struct Data *next;
};

struct Data *head[10];

int hashing(int n)
{
	return n%10;
}

struct Data* initNode(int value)
{
	struct Data* node = (struct Data*)malloc(sizeof(struct Data));
	node->value = value;

	node->next = NULL;
	return node;
}

void deletehash()
{
	int index, value;
	int found = 0;
	struct Data *curr, *curr2;

	printf("Insert Value : ");
	scanf("%d", &value);
	getchar();

	index = hashing(value);
	curr = head[index];
	while(curr != NULL)
	{
		if(curr->value == value)
		{
			found = 1;
			break;
		}
		curr = curr->next;
	}
	if(curr == head[index] && found == 1) //pop head
	{
		head[index] = curr->next;
		free(curr);
		printf("DELETE SUCCESS\n");
		getchar();
	}
	else if(curr->next == NULL && found == 1) //pop tail
	{
		struct Data *curr2 = head[index];
		while(curr2->next != curr)
			curr2 = curr2->next;
		curr2->next = NULL;
		free(curr);
		printf("DELETE SUCCESS\n");
		getchar();
	}
	else if(found == 1) //pop mid
	{
		struct Data *curr2 = head[index];
		while(curr2->next != curr)
			curr2 = curr2->next;
		curr2->next = curr->next;
		free(curr);
		printf("DELETE SUCCESS\n");
		getchar();
	}
	else
	{
		printf("DATA NOT FOUND!\n");
		getchar();
	}

}


void insert()
{
	int value;

	printf("Insert Value : ");
	scanf("%d", &value);
	getchar();

	int hash_value = hashing(value);
	struct Data *curr = head[hash_value];
	if(curr == NULL)
		head[hash_value] = initNode(value);
	else
	{
		while(curr->next !=NULL)
			curr = curr->next;
		curr->next = initNode(value);
	}

	
	printf("SUCCESS ADD NEW DATA!\n");
	getchar();
}

void view()
{
	struct Data* curr = head[0];
	int idx = 0;
	for(int i = 0; i<10; i++){
		printf("%d: ", i);
		curr = head[i];
		while(curr){
			printf("%d   ", curr->value);
			curr = curr->next;
		}
		printf("\n");
	}
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
	int choose = 0;

	do{
		cls();
		printf("Hashing Chaining (practice)\n");
		printf("===========================\n\n");
		printf("Menu :\n");
		printf("=========\n");
		printf("KEY = MOD 10\n");
		printf("1. Insert\n");
		printf("2. View Hash Table\n");
		printf("3. Delete\n");
		printf("4. Exit\n");
		printf("Choose : ");
		scanf("%d", &choose);
		getchar();

		switch(choose)
		{
			case 1 :
				insert();
				break;
			case 2 :
				view();
				getchar();
				break;
			case 3 :
				deletehash();
				break;
		}

	}while(choose != 4);

	return 0;
}