CC=gcc
CFLAGS=-ansi -pedantic -Wall -Werror
EXECUTABLE=fx

all: fx.c
	$(CC) $(CFLAGS) fx.c -o $(EXECUTABLE)

clean:
	rm $(EXECUTABLE)
