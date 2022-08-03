/*
    Author: Diego Palmerin
*/
#include "systemopt.h"

static void getWinSize(struct systemopt * sy) {
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &sy->ws) == -1) {
        printf("getWinSize");
        exit(1);
    }
}

void getCursorPosition(struct systemopt * sy) {
    //Prints current position of cursor
    if(write(STDOUT_FILENO, "\x1b[6n", 4) != 4) {
        printf("getCursorTerminal");
        exit(1);
    }
    //Reads the output generated
    char buff[32];
    int i = 0;
    while(i < 31) {
        if(read(STDIN_FILENO, &buff[i], 1) != 1) {
            printf("getCursorTerminal");
            exit(1);
        }
        if(buff[i] == 'R') break;
        i++;
    }
    buff[i] = '\0';
    // Check if a escape sequence is in the buffer
    if(buff[0] != '\x1b' || buff[1] != '[') {
        exit(1);
    }
    sscanf(&buff[2], "%d;%d", &sy->row, &sy->col);
}
/*
    Disables terminal and sets the terminal to its original state
*/
void finishEditor(struct systemopt * sy) {

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &sy->terminal) == ERROR) {
        printf("finishTerminal");
        exit(1);
    }
}

/*
    Initiates terminal in raw mode(Noncanonical mode)
*/
void initEditor(struct systemopt * sy) {
    if(tcgetattr(STDIN_FILENO, &sy->terminal) == ERROR) {
        printf("InitTerminal");
        exit(1);
    }
    struct termios rawTerminal = sy->terminal;

    rawTerminal.c_lflag &= ~(ICANON | ISIG | IEXTEN | ECHO);

    rawTerminal.c_iflag &= ~(BRKINT | ICRNL | IGNBRK | IGNCR | INLCR |
                             INPCK  | ISTRIP | IXON | PARMRK);

    rawTerminal.c_oflag &= ~OPOST; 

    rawTerminal.c_cc[VMIN] = 1; // Minimum number of bytes to read
    rawTerminal.c_cc[VTIME] = 1; 

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &rawTerminal) == ERROR) {
        printf("InitTerminal");
        exit(1);
    }
    getWinSize(sy);

}
