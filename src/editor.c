#include "editor.h"

void refreshScreen() {
    if(write(STDOUT_FILENO, "\x1b[2J", 4) != 4) {
        printf("RefreshScreen");
        exit(1);
    }
    if(write(STDOUT_FILENO, "\x1b[H", 3) != 3) {
        printf("RefreshScreen");
        exit(1);
    }
}

void moveCursor(int row, int col) {
    char pos[20];
    int temp = sprintf(pos, "\x1b[%d;%dH", row, col);
    if(write(STDOUT_FILENO, pos, temp) != temp) {
        printf("moveCursor");
        exit(1);
    }
}
