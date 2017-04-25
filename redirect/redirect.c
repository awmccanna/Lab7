//
// Created by awmccanna on 4/24/17.
//

#include "redirect.h"


void redirect(char * s)
{
    printf("ATTEMPTING TO REDIRECT\n");
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
    redirectInput(args, type);







    clean(numArgs, args);

}






void redirectInput(char ** args, int type)
{
    pid_t grandparentPID;
    int status, readFD = 0, writeFD = 0;
    FILE * fin = NULL;
    FILE * fout = NULL;
    if(type == 0)
    {
        readFD = openInputFileFD(args[1]);
        writeFD = openOutputFileFD(args[2]);
    }
    else if(type == 1)
    {
        readFD = openInputFileFD(args[1]);
    }
    else if(type == 2)
    {
        writeFD = openOutputFileFD(args[1]);
    }
    printf("read: %d, write: %d\n", readFD, writeFD);

    grandparentPID = fork();
    if(grandparentPID != 0)
    {
        waitpid(grandparentPID, &status, 0);
    }
    else
    {
        pid_t parentPID;


        parentPID = fork();

        if (parentPID != 0)
        {//OUTPUT BLOCK
            if(writeFD > 0) //This will execute if writeFD is > 0, aka we want
            {               //to change where the output is going
                dup2(1, writeFD);
                close(writeFD);
                if(args[2] != NULL)
                    execvp(args[2], args);
                else
                    execvp(args[1], args);
            }

        }// end if AKA parent
        else
        {//INPUT BLOCK
            if(readFD > 0)  //Same as above, this will execute only when we want
            {               //to change the input source.

                dup2(0, readFD);
                close(readFD);
                execvp(args[1], args);
            }

            exit(-1);
        }// end else AKA child
        exit(-1);
    }


    //if(readFD != 0)
      //  close(readFD);
    //if(writeFD != 0)
      //  close(writeFD);


}
