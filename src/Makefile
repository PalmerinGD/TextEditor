# target: dependencies
# 	action

CC = gcc
CFLAGS = -Wall -O2

ed: main.o systemopt.o cnode.o editor.o
	$(CC) main.o systemopt.o cnode.o editor.o $(CFLAGS) -o ed
main.o: main.c
	$(CC) main.c $(CFLAGS) -c -o main.o
systemopt.o: systemopt.c
	$(CC) systemopt.c $(CFLAGS) -c -o systemopt.o
cnode.o: cnode.c
	$(CC) cnode.c $(CFLAGS) -c -o cnode.o
editor.o: editor.c
	$(CC) editor.c $(CFLAGS) -c -o editor.o
