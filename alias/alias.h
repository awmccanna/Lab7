//
// Created by awmccanna on 4/23/17.
//

#ifndef LAB7_ALIAS_H
#define LAB7_ALIAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/myUtils.h"

struct alias
{
    char * value;
    char * key;
};

typedef struct alias Alias;

void cleanTypeAlias(void * ptr);
void * buildTypeAlias(char * command);
char * getAlias(char * k);




#endif //LAB7_ALIAS_H
