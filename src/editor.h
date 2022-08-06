#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum arrows {
    NO_ARROW, ARROW_UP = 65, ARROW_DOWN, ARROW_RIGHT, ARROW_LEFT
};

void refreshScreen();
