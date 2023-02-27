#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "board.h"
#include "text.h"

#define WIDTH 60
#define HEIGHT 30

int *board;
bool whitesturn;
int row, col;

int toScreenX(int x)
{
	return (col - WIDTH) / 2 + x * 6;
}

int toScreenY(int y)
{
	return (row - HEIGHT) / 2 + y * 3;
}

bool isEmpty(int x, int y)
{
	if (board[x + y * 10] == BLANK)
		return true;
	return false;
}

bool forcedToTake(int x, int y)
{
	int color, next;
	int dydx[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

	/*
	Check all diagonals for possible 'double hop'
	Double hop:
	next is opposite color and not blank
	second next spot is empty
	*/

	color = board[x + y * 10];

	for (int i = 0; i < 4; i++)
	{
		if (color != board[x + dydx[i][1] + y + dydx[i][0] * 10] && 
			!isEmpty(x + dydx[i][1], y + dydx[i][0]) && 
			isEmpty(x + 2 * dydx[i][1], y + 2 * dydx[i][0]))
		{
			return true;
		}
	}
	return false;
}

bool checkLegalMove(int x, int y, int nx, int ny)
{
	/*
	Move is legal when:
	ToBe: It is your turn.
		ToDo: If forced to take, it remains your turn.
	The block moves one step diagonally.
	The block skips over another block. Which is 'double' diagonally
	ToBe: The block does not move out of bounds. necessary?
	*/
	int dx = nx - x;
	int dy = ny - y;

	// Check if its your turn
	if ((board[x + y * 10] == WHITE && !whitesturn) ||
		(board[x + y * 10] == BLACK && whitesturn))
		return false;

	// 1 step diagonal move
	if (abs(dx) == 1 && abs(dy) == 1 && board[nx + ny * 10] == BLANK)
		return true;
	else if (abs(dx) == 2 && abs(dy) == 2 &&
			 board[x + dx / 2 + (y + dy / 2) * 10] != board[x + y * 10] &&
			 board[x + dx / 2 + (y + dy / 2) * 10] != BLANK &&
			 (board[x + y * 10] == WHITE || board[x + y * 10] == BLACK))
		return true;
	return false;
}

void movePiece(int x, int y, int nx, int ny)
{

	if (checkLegalMove(x, y, nx, ny))
	{
		if (abs(nx - x) == 2)
		{
			mvprintw(toScreenY(0) - 1, toScreenX(0), "%d", (nx - x));
			refresh();

			board[x + (nx - x) / 2 + (y + (ny - y) / 2) * 10] = BLANK;
		}

		//		if(!forcedToTake(nx,ny))
		whitesturn = !whitesturn;

		board[nx + ny * 10] = board[x + y * 10];
		board[x + y * 10] = BLANK;
	}
}

void toScreenCoords(int *x, int *y, int row, int col)
{
	*x = (col - WIDTH) / 2 + *x * 6;
	*y = (row - HEIGHT) / 2 + *y * 3;
}

int main()
{
	char emesg[] = "I'm sorry but your terminal is too small to play!";

	board = initBoard();

	initscr();
	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	getmaxyx(stdscr, row, col);
	nodelay(stdscr, TRUE);

	// Check if terminal size is large enough to play
	if (row < HEIGHT || col < WIDTH)
	{
		mvprintw(row / 2, (col - strlen(emesg)) / 2, "row: %d, col: %d,  %s",
				 row, col, emesg);
	}

	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_RED);
	init_pair(6, COLOR_WHITE, COLOR_YELLOW);
	init_pair(7, COLOR_WHITE, COLOR_BLUE);

	// Selector coordinates
	int sx = 0, sy = 6;

	bool selected = false;
	int ssx = 0, ssy = 0; // xy selector source
	int tx = 0, ty = 0;	  // xy target

	// gamestarts here
	whitesturn = true;

	pthread_t thread1;
	// pthread_create(&thread1, NULL, *readCheckersCont, NULL);
	erase();
	refresh();
	drawBoard(board, WIDTH, HEIGHT);
	attron(COLOR_PAIR(5));
	mvprintw(toScreenY(sy) + 1, toScreenX(sx) + 2, "  ");
	attroff(COLOR_PAIR(5));
	refresh();

	readCheckers();
	while (1)
	{
		int c;
		c = getch();
		switch (c)
		{
		case KEY_LEFT:
			sx--;
			readCheckers();
			break;
		case KEY_RIGHT:
			sx++;
			readCheckers();
			break;
		case KEY_UP:
			sy--;
			readCheckers();
			break;
		case KEY_DOWN:
			sy++;
			readCheckers();
			break;
		case 'h':
			sx--;
			readCheckers();
			break;
		case 'l':
			sx++;
			readCheckers();
			break;
		case 'k':
			sy--;
			readCheckers();
			break;
		case 'j':
			sy++;
			readCheckers();
			break;
		case ' ':
			readCheckers();
			if (selected)
			{
				tx = sx;
				ty = sy;
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
		drawBoard(board, WIDTH, HEIGHT);
		attron(COLOR_PAIR(selected ? 6 : 5));
		mvprintw(toScreenY(sy) + 1, toScreenX(sx) + 2, "  ");
		attroff(COLOR_PAIR(selected ? 6 : 5));
		evalBoard(board);

		refresh();
	}

	endwin();
	return 0;
}
