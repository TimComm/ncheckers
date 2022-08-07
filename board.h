#ifndef BOARD_H
#define BOARD_H

#include <ncurses.h>

enum state{
	BLANK,
	BLACK,
	WHITE};

int * initBoard();
void printBoard(int * board);
void drawBoard(int * board, int width, int height);

#endif
