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
	char **argv = NULL, s[MAX];
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
	strip(s);

	while(strcmp(s, "exit") != 0)
	{
		pipeCount = containsPipe(s);
		if(pipeCount > 0)
		{
			postPipe = parsePostPipe(s, &postCount);
			prePipe = parsePrePipe(s, &preCount);
			pipeIt(prePipe, postPipe);
			clean(preCount, prePipe);
			clean(postCount, postPipe);
		}// end if pipeCount
        else
        {
            argc = makeargs(s, &argv);
            if(argc != -1)
                forkIt(argv);

            clean(argc, argv);
            argv = NULL;
        }
		if(strlen(s) >= 2)
		{
			if(s[0] == 'c' && s[1] == 'd')
			{
				cd(s);
			}
		}
		if((strstr(s, "<") != NULL) || (strstr(s, ">") != NULL))
		{
			printf("Redirection found\n");
			//TODO redir
		}
		if(strstr(s, "history") != NULL)
        {
			printf("Found history\n");
            //TODO History
        }
        if(strstr(s, "alias") != NULL)
        {
			printf("Found alias\n");
            //TODO alias stuff here
        }


		printf("command?: ");
		fgets(s, MAX, stdin);
		strip(s);

	}// end while

	return 0;

}// end main


