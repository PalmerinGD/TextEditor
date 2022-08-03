# target: dependencies
# 	action

CC = gcc
CFLAGS = -Wall -O2

editor: main.o terminal.o
	$(CC) main.o terminal.o $(CFLAGS) -o editor
main.o: main.c
	$(CC) main.c $(CFLAGS) -c -o main.o
terminal.o: terminal.c
	$(CC) terminal.c $(CFLAGS) -c -o terminal.o
