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
	switch(count%4)
	{
		case 0:
			readCheckersA();
			break;
		case 1:
			readCheckersB();
			break;
		case 2:
			readCheckersC();
			break;
		case 3:
			readCheckersD();
			break;
	}

}

void * readCheckersCont(void *ptr)
{
	while(thread_exit)
	{
		readCheckers();
		sleep(3);
	}
}
void readCheckersA()
{
  char textbuffer[113*11]; // Buffer to store data
  FILE * stream;
  stream = fopen("./dat/txt1.txt", "r");
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

void readCheckersB()
{
  char textbuffer[113*11]; // Buffer to store data
  FILE * stream;
  stream = fopen("./dat/txt2.txt", "r");
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
void readCheckersC()
{
  char textbuffer[113*11]; // Buffer to store data
  FILE * stream;
  stream = fopen("./dat/txt3.txt", "r");
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
void readCheckersD()
{
  char textbuffer[113*11]; // Buffer to store data
  FILE * stream;
  stream = fopen("./dat/txt4.txt", "r");
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
