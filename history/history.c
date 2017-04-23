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




void * buildTypeHistory(char * com)
{
    History * toReturn = (History *) calloc(1, sizeof(History));
    toReturn->command = (char *) calloc(strlen(com), sizeof(char));
    strcpy(toReturn->command, com);
    toReturn->num = makeargs(com, &toReturn->tokCommand);

    return (void *) toReturn;
}





void printTypeHistory(void * passedIn)
{
    History * temp = (History *) passedIn;
    printf("%s\n", temp->command);
}