checkers: main.o board.o text.o
	gcc main.o board.o text.o -o checkers -lncurses

main.o: main.c
	gcc -c main.c

board.o: board.c board.h
	gcc -c board.c board.h

text.o: text.c text.h
	gcc -c text.c text.h

clean:
	rm *.o checkers
