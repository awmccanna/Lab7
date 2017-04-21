#include "pipes.h"

int containsPipe(char *s)
{
	char temp[MAX];
	strcpy(temp, s);
	unsigned int x;
	int count = 0;	
	for(x = 0; x < strlen(temp); x++)
	{
		if(temp[x] == '|')
		{
			count++;
		}
	}

	return count;
}


char ** parsePrePipe(char *s, int * preCount)
{
	char copy[MAX];

	char delim = '|';
	char * save = NULL;
	char ** argv = NULL;

	strcpy(copy, s);

	int count = 0;

	char * token = strtok_r(s, &delim, &s);
	while(token != NULL)
	{
		count++;
		token = strtok_r(NULL, &delim, &s);
	}

	char * temp = strtok_r(copy, &delim, &save);

	int tokens = makeargs(temp, &argv);

	int x;
	for(x = 1; x < count; x++)
	{
		temp = strtok_r(NULL, &delim, &save);
	}


	*preCount = tokens;

	return argv;
}


char ** parsePostPipe(char *s, int * postCount)
{
	char copy[MAX];
	char delim = '|';
	char * save = NULL;
	char ** argv = NULL;

	strcpy(copy, s);


	int count = 0;

	char * token = strtok_r(s, &delim, &s);
	while(token != NULL)
	{
		count++;
		token = strtok_r(NULL, &delim, &s);
	}


	char * temp = strtok_r(copy, &delim, &save);
	int x;
	for(x = 1; x < count; x++)
	{
		temp = strtok_r(NULL, &delim, &save);
	}


	int tokens = makeargs(temp, &argv);
	*postCount = tokens;


	return argv;
}

void pipeIt(char ** prePipe, char ** postPipe)
{
	pid_t parentPID;
	int status;
	parentPID = fork();

	if(parentPID != 0)
	{
		waitpid(parentPID, &status, 0);
	}
	else
	{
		pid_t pid;
		int fd[2], res;

		res = pipe(fd);

		if (res < 0) {
			printf("Pipe Failure\n");
			exit(-1);
		}// end if

		pid = fork();

		if (pid != 0)
		{

			close(fd[1]);
			close(0);
			dup(fd[0]);
			close(fd[0]);
			execvp(postPipe[0], postPipe);

		}// end if AKA parent
		else
		{
			close(fd[0]);
			close(1);
			dup(fd[1]);
			close(fd[1]);
			execvp(prePipe[0], prePipe);
			exit(-1);
		}// end else AKA child
		exit(-1);
	}

}
