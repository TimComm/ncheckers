#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "board.h"

#define WIDTH 60
#define HEIGHT 30

int* board;
int row, col;

bool checkLegalMove(int x, int y, int nx, int ny)
{
	int dx = nx - x;
	int dy = ny - y;
	
	// 1 step diagonal move
	if(abs(dx) == 1 && abs(dy) == 1 && board[nx+ny*10] == BLANK)
		return true;
	else if(abs(dx) == 2 && abs(dy) == 2 && 
		board[x+dx/2+(y+dy/2)*10] != board[x+y*10] &&
		board[x+dx/2+(y+dy/2)*10] != BLANK &&
		(board[x+y*10] == WHITE || board[x+y*10] == BLACK))
		return true;
	return false;
}

void movePiece(int x, int y, int nx, int ny)
{
	if(checkLegalMove(x,y,nx,ny))
	{
		// Remove piece if stepping over DOES NOT WORK YET??
		if(abs(nx-x) == 2)
			board[x+(nx-x)/2+(y+(ny-y)/2)*10] == BLANK;

		board[nx + ny*10] = board[x + y*10];
		board[x + y*10] = BLANK;
	}
}

void toScreenCoords(int* x, int* y, int row, int col)
{
	*x =(col-WIDTH)/2+*x*6;
	*y = (row-HEIGHT)/2+*y*3;
}

int toScreenX(int x)
{
	return (col-WIDTH)/2+x*6;
}

int toScreenY(int y)
{
	return (row-HEIGHT)/2+y*3;
}

int main()
{
	char emesg[] = "I'm sorry but your terminal is too small to play!";
	
	board  = initBoard();
	
	initscr();
	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	getmaxyx(stdscr, row, col);
	nodelay(stdscr, TRUE);
	
	// Check if terminal size is large enough to play
	if (row < HEIGHT || col < WIDTH)
	{
		mvprintw(row/2,(col-strlen(emesg))/2, "row: %d, col: %d,  %s",
			row,col,emesg);
	}

	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_RED);
	init_pair(6, COLOR_WHITE, COLOR_YELLOW);

	// Selector coordinates
	int sx = 0, sy = 0;
	bool selected = false;
	int ssx = 0, ssy = 0;		//xy selector source
	int tx = 0, ty = 0;			//xy target
	


	mvprintw(toScreenY(sy)-1, toScreenX(sx), "sx: %d, sy: %d", sx, sy);

	drawBoard(board,WIDTH,HEIGHT);

	attron(COLOR_PAIR(5));
	mvprintw(toScreenY(sy)+1, toScreenX(sx)+2, "  ");
	attroff(COLOR_PAIR(5));
	refresh();

	while(1)
	{
		int c;
		c = getch();
		switch(c)
		{
			case KEY_LEFT:
				sx--;
				break;
			case KEY_RIGHT:
				sx++;
				break;
			case KEY_UP:
				sy--;
				break;
			case KEY_DOWN:
				sy++;
				break;
			case 'h':
				sx--;
				break;
			case 'l':
				sx++;
				break;
			case 'k':
				sy--;
				break;
			case 'j':
				sy++;
				break;
			case ' ':
				if(selected)
				{
					tx  = sx;
					ty  = sy;
					movePiece(ssx, ssy, tx, ty);
				}
				else
				{
					ssx = sx;
					ssy = sy;
				}
				selected = !selected;
				break;
		}
		// Redraw board + selector.
		erase();
		drawBoard(board,WIDTH,HEIGHT);
		attron(COLOR_PAIR(selected?6:5));
		mvprintw(toScreenY(sy)+1, toScreenX(sx)+2, "  ");
		attroff(COLOR_PAIR(selected?6:5));
		refresh();
	}
	

	endwin();
	return 0;
}