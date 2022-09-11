/*
 * Author: Diego Palmerin
 *
 * */

/*** Includes ***/
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

/*** Defines ***/
#define ERROR -1

/*** Structs ***/
struct systemopt {
    struct termios terminal;
    struct winsize ws;
};

/*** Functions ***/
void initSystemOpt(struct systemopt * sy);
void finishSystemOpt(struct systemopt * sy);
void getWinSize(struct systemopt * sy);
