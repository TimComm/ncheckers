#define HEIGHT 10
#define WIDTH 10
#define WHEIGHT 60
#define WWIDTH 30

#include "board.h"

int boardEval = 0;

int *initBoard()
{
	int i, j;
	static int board[HEIGHT * WIDTH];

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			board[WIDTH * i + j] = BLANK;
		}
	}

	for (i = 0; i < 10; i++)
	{
		if (i < 4)
		{
			for (j = 0; j < 10; j = j + 2)
			{
				board[j + 1 - i % 2 + WIDTH * i] = BLACK;
			}
		}
		else if (i > 5)
		{
			for (j = 0; j < 10; j = j + 2)
			{
				board[j + 1 - i % 2 + WIDTH * i] = WHITE;
			}
		}
	}
	return board;
}

void printBoard(int *board)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			printw("%d", board[j + WIDTH * i]);
		}
		printw("\n");
	}
}

void drawBoard(int *board, int width, int height)
{
	int row, col;
	getmaxyx(stdscr, row, col);

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			switch (board[j + WIDTH * i])
			{
			case 0:
				if ((j + WIDTH * i + i % 2) % 2 == 0)
				{
					attron(COLOR_PAIR(2));
					mvprintw((row - height) / 2 + 3 * i + 0, (col - width) / 2 + 6 * j, "      ");
					mvprintw((row - height) / 2 + 3 * i + 1, (col - width) / 2 + 6 * j, "      ");
					mvprintw((row - height) / 2 + 3 * i + 2, (col - width) / 2 + 6 * j, "      ");
					attroff(COLOR_PAIR(2));
				}
				else
				{
					attron(COLOR_PAIR(1));
					mvprintw((row - height) / 2 + 3 * i + 0, (col - width) / 2 + 6 * j, "      ");
					mvprintw((row - height) / 2 + 3 * i + 1, (col - width) / 2 + 6 * j, "      ");
					mvprintw((row - height) / 2 + 3 * i + 2, (col - width) / 2 + 6 * j, "      ");
					attroff(COLOR_PAIR(1));
				}
				break;
			case 1:
				attron(COLOR_PAIR(4));
				mvprintw((row - height) / 2 + 3 * i + 0, (col - width) / 2 + 6 * j, " /88\\ ");
				mvprintw((row - height) / 2 + 3 * i + 1, (col - width) / 2 + 6 * j, " 8888 ");
				mvprintw((row - height) / 2 + 3 * i + 2, (col - width) / 2 + 6 * j, " \\88/ ");
				attroff(COLOR_PAIR(4));
				break;
			case 2:
				attron(COLOR_PAIR(3));
				mvprintw((row - height) / 2 + 3 * i + 0, (col - width) / 2 + 6 * j, " /88\\ ");
				mvprintw((row - height) / 2 + 3 * i + 1, (col - width) / 2 + 6 * j, " 8888 ");
				mvprintw((row - height) / 2 + 3 * i + 2, (col - width) / 2 + 6 * j, " \\88/  ");
				attroff(COLOR_PAIR(3));
				break;
			}
		}
	}
}

void evalBoard(int *board)
{
	boardEval = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (board[i + j * 10] == WHITE)
				boardEval++;
			else if (board[i + j * 10] == BLACK)
				boardEval--;
		}
	}
	printEval(boardEval);
}

void printEval(int eval)
{
	int row, col;
	getmaxyx(stdscr, row, col);
	int y = (row - WHEIGHT) / 2 + 3 * 10;
	int x = (col - WWIDTH) / 2 + 6 * -4;

	mvprintw(y, x, "   %d", eval);
	for(int i = -10; i < 10; i++)
	{
		attron(COLOR_PAIR((i<eval)?5:7));
		mvprintw(y-i, x, " ");
		attroff(COLOR_PAIR((i<eval)?5:7));
	}

	refresh();
} 
