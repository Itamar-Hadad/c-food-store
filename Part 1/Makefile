CC=gcc
OBJS= board.o game.o main.o
EXEC=2048
DEBUG = -g
CFLAGS = -std=c99  -Wall -Werror $(DEBUG)

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $@

board.o: board.c board.h
game.o: game.c game.h board.h
main.o: main.c game.h

clean: 
	rm -f $(EXEC) $(OBJS)
	
