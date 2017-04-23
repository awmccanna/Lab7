//
// Created by awmccanna on 4/10/17.
//

#include "linkedList.h"


LinkedList * linkedList()
{
	LinkedList * myList = (LinkedList *) calloc(1, sizeof(LinkedList));
	myList->head = (Node *) calloc(1, sizeof(Node));
	myList->tail = (Node *) calloc(1, sizeof(Node));
	myList->head->next = myList->tail;
	myList->tail->prev = myList->head;
    myList->size = 0;
	return myList;
}

void addLast(LinkedList * theList, Node * nn)
{
	if(theList == NULL)
	{
		perror("NULL value passed into addFirst()");
		exit(-99);
	}

	nn->prev = theList->tail->prev;
	nn->next = theList->tail;
	nn->prev->next = nn;
	theList->tail->prev = nn;
	theList->size++;


}



void addFirst(LinkedList* theList, Node * nn)
{
	if(theList == NULL || nn == NULL)
	{
		perror("NULL value passed into addFirst()");
		exit(-99);
	}

	nn->prev = theList->head;
	nn->next = theList->head->next;
	nn->next->prev = nn;
	theList->head->next = nn;


	theList->size++;

}

void removeFirst(LinkedList * theList, void (*removeData)(void *))
{
	if(theList == NULL)
	{
		perror("NULL value passed into addFirst()");
		exit(-99);
	}
	
	Node * cur;
	
	if(theList->head->next != NULL)
	{
		cur = theList->head->next;
		if(cur->next != NULL)
		{
			cur->next->prev = theList->head;
			theList->head->next = cur->next;
			cur->next = NULL;
			cur->prev = NULL;
			removeData(cur->data);
			free(cur);
		}
		else
		{
			removeData(cur->data);
			free(cur);
			theList->head->next = NULL;
		}
				
	}
	theList->size--;

}


void removeLast(LinkedList * theList, void (*removeData)(void *))
{
	if(theList == NULL)
	{
		perror("Null list in printList");
		exit(-99);
	}
	Node * cur = theList->head;

	while(cur->next != NULL)
	{
		cur = cur->next;
	}


	if(cur != theList->head)
	{
		cur->prev->next = NULL;
		cur->prev = NULL;
		removeData(cur->data);
		free(cur);
	}
	theList->size--;

}

void removeItem(LinkedList * theList, Node * nn, void (*removeData)(void *), int (*compare)(const void *, const void *))
{
	if(theList == NULL || nn == NULL)
	{
		perror("Null param in removeItem");
		exit(-99);
	}


	Node * cur = theList->head->next;

	while(cur != NULL)
	{
		if(compare(cur->data, nn->data) == 0)
		{
			if(cur->next != NULL)
				cur->next->prev = cur->prev;

			cur->prev->next = cur->next;
			cur->next = NULL;
			cur->prev = NULL;
			removeData(cur->data);
			free(cur);
			cur = NULL;
			theList->size--;

		}
		else
			cur = cur->next;
	}

	removeData(nn->data);
	free(nn);



}

char * findAlias(LinkedList * theList, char * toFind)
{
	Node * cur = theList->head->next;
	Alias * temp = NULL;
	while(cur != theList->tail)
	{
		temp = (Alias *) cur->data;
		if(strcmp(temp->key, toFind) == 0)
		{
			return temp->value;
		}
		cur = cur->next;
	}

	return NULL;

}










void clearList(LinkedList * theList, void (*removeData)(void *))
{
	if (theList != NULL)
	{
		while (theList->head->next != theList->tail)
		{
			removeFirst(theList, removeData);
		}
		free(theList->head);
		free(theList->tail);
	}
}


void printList(const LinkedList * theList, void (*convertData)(void *), int numPrint)
{
	if(theList == NULL)
	{
		perror("Null list in printList");
		exit(-99);
	}

	int totalNum = numPrint;
    int numPosition = theList->size;
    int printThisOne = 1;
    if(totalNum > 0)
    {
        Node * cur = theList->head->next;
        if(totalNum > theList->size)
        {
            while(cur->data != NULL)
            {
                printf("%d. ", printThisOne++);
                numPosition--;
                convertData(cur->data);
                cur = cur->next;
            }
        }
        else
        {
            while(totalNum >= 0)
            {
                printf("%d. ", printThisOne++);
                numPosition--;
                convertData(cur->data);
                cur = cur->next;
                totalNum--;
            }
        }

    }




}


void printList_file(const LinkedList * theList, void (*convertData)(void *, FILE *), int numPrint)
{
    if(theList == NULL)
    {
        perror("Null list in printList");
        exit(-99);
    }


    FILE * fout = openRCHistory();


    int totalNum = numPrint;
    int numPosition = theList->size;
    int printThisOne = 1;
    if(totalNum > 0)
    {
        Node * cur = theList->head->next;
        if(totalNum > theList->size)
        {
            while(cur->data != NULL)
            {
                fprintf(fout, "%d. ", printThisOne++);
                numPosition--;
                convertData(cur->data, fout);
                cur = cur->next;
            }
        }
        else
        {
            while(totalNum >= 0)
            {
                fprintf(fout, "%d. ", printThisOne++);
                numPosition--;
                convertData(cur->data, fout);
                cur = cur->next;
                totalNum--;
            }
        }
        fclose(fout);
    }
}




















