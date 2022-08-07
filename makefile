checkers: main.o board.o
	gcc main.o board.o -o checkers -lncurses

main.o: main.c
	gcc -c main.c

board.o: board.c board.h
	gcc -c board.c board.h

clean:
	rm *.o checkers
