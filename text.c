#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "text.h"
int count = 0;
volatile int thread_exit = 1;
void readCheckers()
{
	count++;
	readCheckers2(count%4);
	
}

void * readCheckersCont(void *ptr)
{
	while(thread_exit)
	{
		readCheckers();
		sleep(3);
	}
}
void readCheckers2(int A)
{
	FILE * stream;
	switch(A)
	{
		case 0: 
			stream = fopen("./dat/txt1.txt", "r");
			break;
		case 1:
			stream = fopen("./dat/txt2.txt", "r");
			break;
		case 2:
			stream = fopen("./dat/txt3.txt", "r");
			break;;
		case 3:
			stream = fopen("./dat/txt4.txt", "r");
			break;
		
	}

  char textbuffer[113*11]; // Buffer to store data
  fread(&textbuffer, sizeof(char), 113*11, stream);
  fclose(stream);
  // Printing data to check validity
  int x;
  x = getmaxx(stdscr);
  for (int j=0; j < 11; j++)
  {
	  for (int i = 0; i < 112; i++)
	  {
		  mvprintw(j,x/2-112/2+i,"%c", textbuffer[i+j*112+j]);
	  }
  }
}

