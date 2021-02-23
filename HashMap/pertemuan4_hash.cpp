#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Data {
	char word[100];
	int key;
	Data *next;
}*head[50], *curr, *tail[50];

int hashByAlphabet(char word[100]) {
	return word[0] - 97;
}

void addtoTable(char word[100]) {
	int indexToInsert = hashByAlphabet(word);
	
	curr = (Data*)malloc(sizeof(Data));
	strcpy(curr->word, word);
	curr->key = indexToInsert;
	
	if (head[indexToInsert] == NULL) {
		head[indexToInsert] = tail[indexToInsert] = curr;
	} else {
		tail[indexToInsert]->next = curr;
		tail[indexToInsert] = curr;
	}
	tail[indexToInsert]->next = NULL;
}

// 0 -> abc - ali 
// 1 -> budi - bima

void viewList(int index) {
	curr = head[index];
	while(curr!=NULL) {
		printf("%s - ", curr->word);
		curr = curr->next;
	}
}


void viewTable() {
	int i=0;
	int size = 50;
	for (i=0;i<size;i++) {
		printf("\n%d -> ", i);
		viewList(i);
	}
}

// function returning node that has word
Data* getData(char word[100]) {
	int i=0;
	int size = 50;
	int index = hashByAlphabet(word);
	curr = head[index];
	while(curr != NULL) {
		if (strcmp(curr->word, word) == 0) {
			return curr;
		}
		curr = curr->next;
	}
	return NULL;
}

int main() {

	addtoTable("define");addtoTable("atan");
	addtoTable("char");addtoTable("charlie");
	addtoTable("charles");addtoTable("acos");
	Data *myData = getData("define");
	printf("data %s", myData->word); // 
	
	viewTable();
	
	return 0;
}
