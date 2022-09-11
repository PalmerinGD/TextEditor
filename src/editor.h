#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "cnode.h"
#include "systemopt.h"

#define ESC '\x1b'
#define IS_RUNNING 1
#define CTRL_KEY(k) ((k & 0x1f))
#define ENTER_KEY '\r'

struct editor {
    struct cnodeList cl;
    struct systemopt sy;
    unsigned int row, col;
    unsigned int totalRows, totalColumns;
    unsigned int offsetPosition;
};

void initEditor(struct editor * e);

int printTextToScreen(int fd, struct editor * e);
void finishEditor(struct editor * e);
void refreshScreen();
void updateCursor(const unsigned int row, const unsigned int col);
void addCharacter(struct editor * e, char c);
void moveCursorUp(struct editor * e);
void moveCursorDown(struct editor * e);
void moveCursorLeft(struct editor * e);
void moveCursorRight(struct editor * e);
void deleteCharacter(struct editor * e);

void updateOffsetPosition(struct editor * e);
