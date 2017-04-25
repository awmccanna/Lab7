//
// Created by awmccanna on 4/24/17.
//

#ifndef LAB7_REDIRECT_H
#define LAB7_REDIRECT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../tokenize/makeArgs.h"
#include "../utils/fileUtil.h"


void redirect(char * s);
void redirectInput(char **,char ** args, int type);








#endif //LAB7_REDIRECT_H
