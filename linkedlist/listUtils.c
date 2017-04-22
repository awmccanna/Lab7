//
// Created by awmccanna on 4/10/17.
//

#include "listUtils.h"
#include "../words/word.h"

Node * buildNode(FILE * fin, void *(*buildData)(FILE * in) )
{

	Node * nn = buildNode_Type(buildData(fin));
	return nn;
}

Node * buildNode_Type(void * passedIn)
{

	Node * nn = (Node *) calloc(1, sizeof(Node));
	nn->data = passedIn;
	return nn;
}

void sort(LinkedList * theList, int (*compare)(const void *, const void *))
{
    if(theList == NULL)
    {
        perror("Null linked list in buildListTotal.");
        exit(-99);
    }
    if(theList->size > 1)
    {
        Node *start, *search, *min;
        void *temp;

        for(start = theList->head->next; start->next != NULL; start = start->next)
        {
            min = start;
            for(search = start->next; search != NULL; search = search->next)
            {
                if(compare(search->data, min->data) < 0)
                    min = search;
            }

            temp = min->data;
            min->data = start->data;
            start->data = temp;
        }

    }

}

void buildListTotal(LinkedList * myList, int total, FILE * fin, void * (*buildData)(FILE * in))
{
    if(myList == NULL)
    {
        perror("Null linked list in buildListTotal.");
        exit(-99);
    }
    if(total <= 0 )
    {
        perror("Invalid total in buildListTotal");
        exit(-99);
    }

	int i = 0;
    for(i; i<total; i++)
    {
        Node *nn = buildNode(fin, buildData);
        addFirst(myList, nn);
    }



}
