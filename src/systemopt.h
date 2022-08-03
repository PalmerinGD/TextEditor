/*
 * Author: Diego Palmerin
 *
 * */

#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#define ERROR -1

struct systemopt {
    struct termios terminal;
    struct winsize ws;
    int row;
    int col;
};

/* Private Functions */
static void getWinSize(struct systemopt * sy);

/* Public Functions */
void initEditor(struct systemopt * sy);
void finishEditor(struct systemopt * sy);
void getCursorPosition(struct systemopt * sy);
