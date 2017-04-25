//
// Created by awmccanna on 4/24/17.
//

#include "redirect.h"


void redirect(char * s)
{

    char copy[MAX];
    strcpy(copy, s);
    strip(copy);
    char ** args = NULL;
    int type = -1;//0 == do both, 1 == input only, 2 == output only
    if(strstr(s, "<") != NULL && strstr(s, ">") != NULL)
    {
        type = 0;
    }
    else if(strstr(s, "<") != NULL)
    {
        type = 1;
    }
    else if(strstr(s, ">") != NULL)
    {
        type = 2;
    }
    int numArgs = makeArgsBang(copy, &args);
    char ** hope = NULL;
    int testArgs = makeargs(args[0], &hope);



    redirectInput(hope, args, type);






    clean(testArgs, hope);
    clean(numArgs, args);

}






void redirectInput(char ** hope, char ** args, int type)
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
        if(type == 0)
        {
            freopen(args[1], "r", stdin);
            freopen(args[2], "w", stdout);
        }
        else if(type == 1)
        {
            freopen(args[1], "r", stdin);
        }
        else if(type == 2)
        {
            freopen(args[1], "w", stdout);
        }

        execvp(hope[0], hope);
        exit(-1);





    }



}
