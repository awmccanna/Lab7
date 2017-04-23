//
// Created by awmccanna on 4/23/17.
//

#include "alias.h"

void cleanTypeAlias(void * ptr)
{
    Alias * temp = (Alias *) ptr;
    free(temp->key);
    free(temp->value);
    free(temp);
}


void * buildTypeAlias(char * command)
{
    Alias * toReturn = (Alias *) calloc(1, sizeof(Alias));

    //Seperating the command in single quotes out to be stored as the
    //value of the alias
    char ** firstToken = NULL;
    char copy1[MAX];
    strcpy(copy1, command);
    strip(copy1);
    int first = makeArgsSingleQuote(copy1, &firstToken);
    toReturn->value = (char *) calloc(strlen(firstToken[1])+1, sizeof(char));
    strcpy(toReturn->value, firstToken[1]);

    //Getting the key of the alias. Seperating by spaces, then removing the
    //= sign
    char ** secondToken = NULL;
    char copy2[MAX];
    strcpy(copy2, firstToken[0]);
    strip(copy2);
    int second = makeargs(copy2, &secondToken);
    unsigned int x = (unsigned int)strlen(secondToken[1]);
    secondToken[1][x-1] = '\0';
    toReturn->key = (char *) calloc(strlen(secondToken[1])+1, sizeof(char));
    strcpy(toReturn->key, secondToken[1]);

    clean(first, firstToken);
    clean(second, secondToken);
    return (void *) toReturn;
}



char * getAlias(char * k)
{

}