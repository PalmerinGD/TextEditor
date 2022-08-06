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
