#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#define ERROR -1

struct editor {
    struct termios terminalConfig;
    struct winsize ws;
    int row;
    int col;
};

void initEditor(struct editor * e);
void finishEditor(struct editor * e);
void getCursorPosition(struct editor * e);
void getWinSize(struct winsize * ws);
