# target: dependencies
# 	action

CC = gcc
CFLAGS = -Wall -O2

editor: main.o systemopt.o cnode.o
	$(CC) main.o systemopt.o cnode.o $(CFLAGS) -o editor
main.o: main.c
	$(CC) main.c $(CFLAGS) -c -o main.o
systemopt.o: systemopt.c
	$(CC) systemopt.c $(CFLAGS) -c -o systemopt.o
cnode.o: cnode.c
	$(CC) cnode.c $(CFLAGS) -c -o cnode.o
