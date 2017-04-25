/**
 * Alex McCanna
 * CSCD 340 Lab 7
 * Shell
 *
 * ---Known issues---
 * ~Piping does not work with aliases
 * ~Cannot pipe multiple times
 * ~Crashes on file not found during redirection of input
 *
 */


#include "./pipes/pipes.h"
#include "./utils/myUtils.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"
#include "./changeDir/changeDir.h"
#include "./linkedlist/linkedList.h"
#include "./linkedlist/listUtils.h"
#include "./history/history.h"
#include "./alias/alias.h"
#include "./utils/fileUtil.h"
#include "./redirect/redirect.h"


int main()
{
	int argc, pipeCount, lineCount, HISTCOUNT, HISTFILECOUNT;
	char **argv = NULL, s[MAX], copy[MAX], pipeCopy[MAX], a[MAX], lineIn[MAX];
	int preCount = 0, postCount = 0;
	char ** prePipe = NULL, ** postPipe = NULL;
	LinkedList *history = linkedList();
    LinkedList *alias = linkedList();
	FILE * fin = openRC();
    int linesLeft = 0;
	if(fin == NULL)
	{
		HISTCOUNT = 100;
		HISTFILECOUNT = 1000;
	}
	else
	{
        lineCount = countRecords(fin, 1);
		getCounts(fin, &HISTCOUNT, &HISTFILECOUNT);

        for(linesLeft; linesLeft < lineCount-2; linesLeft++)
        {
            fgets(lineIn, MAX, fin);
            strip(lineIn);
            if(lineIn[0] != '\0' && lineIn[0] != '\n')
            {
                strcpy(a, lineIn);
                strip(a);
                addLast(alias, buildNode(a, buildTypeAlias));
            }

        }

	}
	fclose(fin);

	printf("command?: ");
	fgets(s, MAX, stdin);
    strip(s);
    if(strstr(s, "!!") != NULL)
    {
        printf("No history yet.\n");
    }
    else if(strstr(s, "!") != NULL)
    {
        printf("No history yet.\n");
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

        /**
         * Redirection block. calls the redirect() method
         */
        if ((strstr(copy, "<") != NULL) || (strstr(copy, ">") != NULL))
        {
            redirect(s);
        }


        /**
         * if there was no redirection, the program will continue as normal
         */
        else
        {
            /**
             * PIPE
             */
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




            /**CHANGE DIRECTORY
             * used to change directory if cd are the first two characters
             */
            if (strlen(copy) >= 2)
            {
                if (copy[0] == 'c' && copy[1] == 'd') {
                    cd(copy);
                }
            }











            /**HISTORY
             * prints the history linkedlist
             */
            if (strstr(copy, "history") != NULL)
            {
                printList(history, printTypeHistory, HISTCOUNT);
            }






            /**ALIAS
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







        }

        /**
         * STARTING THE WHOLE PROCESS OVER AGAIN
         */

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
            char ** histArgs = NULL;
            History * h = NULL;
            int histNum = makeArgsBang(s, &histArgs);
            int numToWalk = atoi(histArgs[0]);
            if(numToWalk <= history->size)
            {
                int i = 1;
                Node * cur = history->head->next;
                for(i; i < numToWalk; i++)
                {
                    cur = cur->next;
                }
                if(cur->data == NULL || cur == history->tail)
                    printf("Uh oh, went too far.\n");
                else
                    h = (History *) cur->data;
                if(h->command != NULL)
                    strcpy(s, h->command);
            }
            else
            {
                printf("Command not possible\n");
            }

            clean(histNum, histArgs);

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









































