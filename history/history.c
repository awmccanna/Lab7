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
    free(in);

}




void * buildTypeHistory(char * com)
{
    History * toReturn = (History *) calloc(1, sizeof(History));
    toReturn->command = (char *) calloc(strlen(com)+1, sizeof(char));
    strcpy(toReturn->command, com);

    return (void *) toReturn;
}





void printTypeHistory(void * passedIn)
{
    History * temp = (History *) passedIn;
    printf("%s\n", temp->command);
}

void printTypeHistory_file(void * passedIn, FILE * fout)
{
    History * temp = (History *) passedIn;
    fprintf(fout, "%s\n", temp->command);
}