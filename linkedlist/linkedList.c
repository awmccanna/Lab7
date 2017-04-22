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


void printList(const LinkedList * theList, void (*convertData)(void *))
{
	if(theList == NULL)
	{
		perror("Null list in printList");
		exit(-99);
	}
	
	Node * cur = theList->head->next;
	while(cur != NULL)
	{
		convertData(cur->data);
		cur = cur->next;		
	}

	
	
}






















