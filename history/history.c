//
// Created by awmccanna on 4/22/17.
//

#include "history.h"

void cleanTypeHistory(void * ptr)
{
    if(ptr == NULL)
    {
        perror("Null pointer passing into cleanTypeMovie()");
        exit(-99);
    }

    History * in = (History *) ptr;

    free(in->command);

    int i = 0;
    for(i; i < in->num; i++)
    {
        free(in->tokCommand[i]);
    }
    free(in->tokCommand);

}




void buildTypeHistory(char * com, char ** tCom, int numCom)
{




}





void printTypeHistory(void * passedIn)
{
    History * temp = (History *) passedIn;
    printf("%d. %s\n", temp->num, temp->command);
}