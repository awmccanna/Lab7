//
// Created by awmccanna on 4/22/17.
//

#include "changeDir.h"

void cd(char * s)
{
	char ** argv = NULL;
	int args = makeargs(s, &argv);
    chdir(argv[1]);
    clean(args, argv);
}