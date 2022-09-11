/*
    Author: Diego Palmerin
*/
#include "systemopt.h"

void getWinSize(struct systemopt * sy) {
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &sy->ws) == -1) {
        printf("getWinSize");
        exit(1);
    }
}

/*
    Disables terminal and sets the terminal to its original state
*/
void finishSystemOpt(struct systemopt * sy) {

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &sy->terminal) == ERROR) {
        printf("finishTerminal");
        exit(1);
    }
}

/*
    Initiates terminal in raw mode(Noncanonical mode)
*/
void initSystemOpt(struct systemopt * sy) {
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

