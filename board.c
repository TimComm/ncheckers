#define HEIGHT 10
#define WIDTH 10

#include "board.h"

int * initBoard()
{   
	int i,j;

	static int board[HEIGHT*WIDTH];

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			board[WIDTH*i+j] = BLANK; 
		}
	}

	for (i = 0; i < 10; i++)
	{
		if(i < 4)
		{
			for(j = 0; j < 10; j = j +2)
			{
				board[j+1-i%2+WIDTH*i] = BLACK;
			}
		}
		else if(i > 5)
		{
			for(j = 0; j < 10; j = j +2)
			{
				board[j+1-i%2+WIDTH*i] = WHITE;
			}
		}
	}
    return board;
}

void printBoard(int * board)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			printw("%d", board[j+WIDTH*i]);
		}
		printw("\n");
	}
}

void drawBoard(int * board, int width, int height)
{
	int row, col;

	getmaxyx(stdscr, row, col);
	
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			switch(board[j + WIDTH*i]) 
			{
				case 0:
					if((j + WIDTH*i+i%2)%2 == 0)
					{
						attron(COLOR_PAIR(2));
						mvprintw((row-height)/2+3*i+0, (col-width)/2+6*j, "      ");
						mvprintw((row-height)/2+3*i+1, (col-width)/2+6*j, "      ");
						mvprintw((row-height)/2+3*i+2, (col-width)/2+6*j, "      ");
						attroff(COLOR_PAIR(2));
					}
					else
					{
						attron(COLOR_PAIR(1));
						mvprintw((row-height)/2+3*i+0, (col-width)/2+6*j, "      ");
						mvprintw((row-height)/2+3*i+1, (col-width)/2+6*j, "      ");
						mvprintw((row-height)/2+3*i+2, (col-width)/2+6*j, "      ");
						attroff(COLOR_PAIR(1));
					 }	
					break;
				case 1:
					attron(COLOR_PAIR(4));
					mvprintw((row-height)/2+3*i+0, (col-width)/2+6*j, " /88\\ ");
					mvprintw((row-height)/2+3*i+1, (col-width)/2+6*j, " 8888 ");
					mvprintw((row-height)/2+3*i+2, (col-width)/2+6*j, " \\88/ ");
					attroff(COLOR_PAIR(4));
					break;
				case 2: 
					attron(COLOR_PAIR(3));
					mvprintw((row-height)/2+3*i+0, (col-width)/2+6*j, " /88\\ ");
					mvprintw((row-height)/2+3*i+1, (col-width)/2+6*j, " 8888 ");
					mvprintw((row-height)/2+3*i+2, (col-width)/2+6*j, " \\88/  ");
					attroff(COLOR_PAIR(3));
					break;
			} 
		}
	}
		
}





