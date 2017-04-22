//
// Created by awmccanna on 4/20/17.
//
#include "./pipes/pipes.h"
#include "./utils/myUtils.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"
#include "./changeDir/changeDir.h"

int main()
{
	int argc, pipeCount, HISTCOUNT, HISTFILECOUNT;
	char **argv = NULL, s[MAX], copy[MAX];
	int preCount = 0, postCount = 0;
	char ** prePipe = NULL, ** postPipe = NULL;
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
    strcpy(copy, s);
	strip(s);
    strip(copy);

	while(strcmp(s, "exit") != 0)
	{
		pipeCount = containsPipe(s);

		if(pipeCount > 0)
		{
            strcpy(copy, s);
			postPipe = parsePostPipe(copy, &postCount);
			prePipe = parsePrePipe(copy, &preCount);
			pipeIt(prePipe, postPipe);
			clean(preCount, prePipe);
			clean(postCount, postPipe);
		}// end if pipeCount
        else
        {
            strcpy(copy, s);
            argc = makeargs(copy, &argv);
            if(argc != -1)
                forkIt(argv);

            clean(argc, argv);
            argv = NULL;
        }
		if(strlen(copy) >= 2)
		{
			if(copy[0] == 'c' && copy[1] == 'd')
			{
				cd(copy);
			}
		}
		if((strstr(copy, "<") != NULL) || (strstr(copy, ">") != NULL))
		{
			printf("Redirection found\n");
			//TODO redir
		}
		if(strstr(copy, "history") != NULL)
        {
			printf("Found history\n");
            //TODO History
        }
        if(strstr(copy, "alias") != NULL)
        {
			printf("Found alias\n");
            //TODO alias stuff here
        }


		printf("command?: ");
		fgets(s, MAX, stdin);
        strcpy(copy, s);
        strip(s);
        strip(copy);

	}// end while

	return 0;

}// end main


