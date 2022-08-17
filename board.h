#ifndef BOARD_H
#define BOARD_H

#include <ncurses.h>

extern int boardEval;
enum state{
	BLANK,
	BLACK,
	WHITE};

int * initBoard();
void printBoard(int * board);
void drawBoard(int * board, int width, int height);
void evalBoard();
void printEval(int eval);

#endif
