CC=gcc
CFLAGS=-ansi -pedantic -Wall -Werror

all: fx.c
	$(CC) $(CFLAGS) fx.c -o fx