#include "myUtils.h"

void strip(char *array)
{
	if(array == NULL)
	{
		perror("array is null");
		exit(-99);
	}// end if

	int len = strlen(array), x = 0;
   
	while(array[x] != '\0' && x < len)
	{
	  if(array[x] == '\r')
		 array[x] = '\0';

	  else if(array[x] == '\n')
		 array[x] = '\0';

	  x++;

}// end while
   
}// end strip

int menu()
{
   char temp[MAX];
   int choice;
   printf("1) Print the list\n");
   printf("2) Add First\n");
   printf("3) Add Last\n");
   printf("4) Sort\n");
   printf("5) Remove Item\n"); 
   printf("6) Quit\n"); 
   printf("Choice --> ");
   fgets(temp, MAX, stdin);
   choice = atoi(temp);

   
   while(choice < 1 || choice > 6)
   {
	  printf("1) Print the list\n");
	  printf("2) Add First\n");
	  printf("3) Add Last\n");
	  printf("4) Sort\n");
	  printf("5) Remove Item\n");
	  printf("6) Quit\n");
	  printf("Choice --> ");
	  fgets(temp, MAX, stdin);
	  choice = atoi(temp);
   
   }// end while

   return choice;
   
}// end menu


FILE * openRC()
{
	char rc[] = ".ushrc";
	FILE * fin = NULL;
	fin = fopen(rc, "r");
	return fin;
}

void getCounts(FILE * fin, int * histCount, int * histFileCount)
{
	char temp1[MAX];
	char temp2[MAX];

    char ** token1 = NULL;
    char ** token2 = NULL;

	fgets(temp1, MAX, fin);
	fgets(temp2, MAX, fin);

	strip(temp1);
	strip(temp2);

    int num1 = makeArgsEqual(temp1, &token1);
    int num2 = makeArgsEqual(temp2, &token2);

    if(strcmp(token1[0], "HISTCOUNT") == 0)
    {
        *histCount = atoi(token1[1]);
        *histFileCount = atoi(token2[1]);
    }
    else
    {
        *histCount = atoi(token2[1]);
        *histFileCount = atoi(token1[1]);
    }

    clean(num1, token1);
    clean(num2, token2);

}



























