//
// Created by awmccanna on 4/22/17.
//

#ifndef LAB7_HISTORY_H
#define LAB7_HISTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tokenize/makeArgs.h"


struct history
{
    char * command;
};

typedef struct history History;

void cleanTypeHistory(void * ptr);
void * buildTypeHistory(char * com);
void printTypeHistory(void * passedIn);
void printTypeHistory_file(void * passedIn, FILE * fout);



#endif //LAB7_HISTORY_H
