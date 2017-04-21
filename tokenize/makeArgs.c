#include "makeArgs.h"

/*
 * Alex McCanna
 * CSCD 340
 * Lab 6
 */

void clean(int argc, char **argv)
{
    int i = 0;
    for(i; i < argc; i++)
    {
        free(argv[i]);
    }
    free(argv);

}// end clean

void printargs(int argc, char **argv)
{
	int x;
	for(x = 0; x < argc; x++)
		printf("%s\n", argv[x]);

}// end printargs

int makeargs(char *s, char *** argv)
{
	char copy[MAX];
	strcpy(copy, s);
	unsigned int count = 0;
	char * ph;

	char * token = strtok_r(s, " ", &s);
	while(token != NULL)
	{
		count++;
		token = strtok_r(NULL, " ", &s);
	}


    *argv = (char **) calloc(count+1, sizeof(char*));
    token = strtok_r(copy, " ", &ph);
    (*argv)[0] = (char *) calloc(strlen(token)+1, sizeof(char));
    strcpy((*argv)[0], token);

	int x;
	for(x = 1; x < count; x++)
	{
		token = strtok_r(NULL, " ", &ph);
        (*argv)[x] = (char *) calloc(strlen(token)+1, sizeof(char));
        strcpy((*argv)[x], token);

	}

	return count;

}// end makeArgs





int makeArgsEqual(char *s, char *** argv)
{
	char copy[MAX];
	strcpy(copy, s);
	unsigned int count = 0;
	char * ph;

	char * token = strtok_r(s, "=", &s);
	while(token != NULL)
	{
		count++;
		token = strtok_r(NULL, "=", &s);
	}


	*argv = (char **) calloc(count+1, sizeof(char*));
	token = strtok_r(copy, "=", &ph);
	(*argv)[0] = (char *) calloc(strlen(token)+1, sizeof(char));
	strcpy((*argv)[0], token);

	int x;
	for(x = 1; x < count; x++)
	{
		token = strtok_r(NULL, "=", &ph);
		(*argv)[x] = (char *) calloc(strlen(token)+1, sizeof(char));
		strcpy((*argv)[x], token);

	}

	return count;

}// end makeArgs
























