//
// Created by awmccanna on 4/20/17.
//
#include "./pipes/pipes.h"
#include "./utils/myUtils.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"
#include "./changeDir/changeDir.h"
#include "./linkedlist/linkedList.h"
#include "./linkedlist/listUtils.h"
#include "./history/history.h"
#include "./alias/alias.h"


int main()
{
	int argc, pipeCount, HISTCOUNT, HISTFILECOUNT;
	char **argv = NULL, s[MAX], copy[MAX], pipeCopy[MAX];
	int preCount = 0, postCount = 0;
	char ** prePipe = NULL, ** postPipe = NULL;
	LinkedList *history = linkedList();
    LinkedList *alias = linkedList();
	FILE * fin = openRC();
	if(fin == NULL)
	{
		HISTCOUNT = 100;
		HISTFILECOUNT = 1000;
	}
	else
	{
		getCounts(fin, &HISTCOUNT, &HISTFILECOUNT);
	}

	//printf("HISTCOUNT: %d, HISTFILECOUNT: %d\n", HISTCOUNT, HISTFILECOUNT);

	fclose(fin);

	printf("command?: ");
	fgets(s, MAX, stdin);
    strip(s);
    if(strstr(s, "!!") != NULL)
    {
        printf("No previous commands\n");
    }
    else if(strstr(s, "!") != NULL)
    {
        printf("History by command number not implemented yet\n");
    }

    /**
     * This next block of code tests for an alias. It does this by looking
     * through the alias linked list for a match to the given input string.
     * If a match is found to the input (the key), then an associated value
     * is returned.
     */
    char * aliasTest = findAlias(alias, s);
    if(aliasTest != NULL)
    {
        strcpy(s, aliasTest);
    }
	strcpy(copy, s);
	strcpy(pipeCopy, s);
	strip(copy);
	strip(pipeCopy);


	//Add to history part here
    char addHist[MAX];
    strcpy(addHist, s);
    strip(addHist);
    addLast(history, buildNode(addHist, buildTypeHistory));


	while(strcmp(s, "exit") != 0)
	{

		pipeCount = containsPipe(pipeCopy);
		if (pipeCount > 0)
		{
			postPipe = parsePostPipe(pipeCopy, &postCount);
			prePipe = parsePrePipe(pipeCopy, &preCount);
			pipeIt(prePipe, postPipe);
			clean(preCount, prePipe);
			clean(postCount, postPipe);
		}// end if pipeCount
		else
        {
			argc = makeargs(pipeCopy, &argv);
			if (argc != -1)
				forkIt(argv);

			clean(argc, argv);
			argv = NULL;
		}




        /**
         * used to change directory if cd are the first two characters
         */
		if (strlen(copy) >= 2)
		{
			if (copy[0] == 'c' && copy[1] == 'd') {
				cd(copy);
			}
		}








		if ((strstr(copy, "<") != NULL) || (strstr(copy, ">") != NULL))
		{
			printf("Redirection found\n");
			//TODO redir
		}



        /**
         * prints the history linkedlist
         */
		if (strstr(copy, "history") != NULL)
		{
            printList(history, printTypeHistory, HISTCOUNT);
		}






        /**
         * Alias checking code. If the word alias is found, this will execute
         * attempt to create an alias for the command.
         * Aliases are stored in a linkedList, which will be searched through
         * if a call is made
         */
		if (strstr(copy, "alias") != NULL)
		{
            char aliasCopy[MAX];
            strcpy(aliasCopy, s);
            strip(aliasCopy);
			addLast(alias, buildNode(aliasCopy, buildTypeAlias));
		}


		printf("command?: ");
		fgets(s, MAX, stdin);
        strip(s);
        if(strstr(s, "!!") != NULL)
        {
            if(history->size == 0)
            {
                printf("No previous commands\n");
            }
            else
            {
                History * temp = (History *) history->tail->prev->data;
                strcpy(s, temp->command);
            }
        }
        else if(strstr(s, "!") != NULL)
        {
            printf("History by command number not implemented yet\n");
        }

        /**
         * This next block of code tests for an alias. It does this by looking
         * through the alias linked list for a match to the given input string.
         * If a match is found to the input (the key), then an associated value
         * is returned.
         */
        aliasTest = findAlias(alias, s);
        if(aliasTest != NULL)
        {
            strcpy(s, aliasTest);
        }
		strcpy(copy, s);
		strcpy(pipeCopy, s);
		strip(s);
		strip(copy);
		strip(pipeCopy);

        /**
         * Checking for duplicates before adding history
         */
		if (history->tail->prev->data != NULL)
		{
			char addHistAgain[MAX];
			History *curHist = (History *) history->tail->prev->data;
			strcpy(addHistAgain, s);
			strip(addHistAgain);
			if (strcmp(addHistAgain, curHist->command) != 0)
			{
				addLast(history, buildNode(addHistAgain, buildTypeHistory));
			}

		}// end while
	}

    printList_file(history, printTypeHistory_file, HISTFILECOUNT);
	clearList(history, cleanTypeHistory);
	free(history);
    clearList(alias, cleanTypeAlias);
    free(alias);
	return 0;

}// end main









































