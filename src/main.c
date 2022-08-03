#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "terminal.h"

#define ENTER 13
#define IS_RUNNING 1
#define CTRL_KEY(k) ((k & 0x1f))
struct Cnode {
    char c;
    struct Cnode * next;
    struct Cnode * prev;
};

struct  CnodeList{
    int totalCnodes;
    struct Cnode * begin;
    struct Cnode * end;
};

struct TextEditor {
    int totalRows;
    int totalCharacters;
    struct CnodeList * rows;
    struct Cnode * currentPosition;
    struct CnodeList * currentRow;
};


void refreshScreen() {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
}

int main() {
    struct editor e;
    initEditor(&e);
    char c;

    struct TextEditor text;
    text.totalRows = 1;
    text.totalCharacters = 0;
    text.rows = NULL;
    text.currentPosition = NULL;
    text.currentRow = NULL;

    text.currentRow = text.rows = calloc(1,sizeof(struct CnodeList));

    text.rows->totalCnodes = 0;
    text.rows->begin = NULL;
    text.rows->end = NULL;

    text.rows->begin = text.currentPosition = calloc(1, sizeof(struct Cnode));


    while(IS_RUNNING) {
        refreshScreen();
        if(text.totalCharacters > 0) {

            for(int i=0; i<text.totalRows; i++) {


                int totalBytesToWrite = text.rows[i].totalCnodes;

                printf("total: %d\n", totalBytesToWrite);

                char * buffer = calloc(totalBytesToWrite, 1);

                struct Cnode * characterToPrint = text.rows[i].begin;

                for(int j=0; j<(int)totalBytesToWrite; j++) {
                    buffer[j] = characterToPrint->c;
                    characterToPrint = characterToPrint->next;
                }

                write(STDOUT_FILENO, buffer, totalBytesToWrite);
                free(buffer);
            }

        }
        if(read(STDIN_FILENO, &c, 1) == -1) break;
        if(c == CTRL_KEY('q')) break;
        else if(c == ENTER) {
        }
        else if(c == '\x1b') {
            //Change in read one for two
            if(read(STDIN_FILENO, &c, 1) == -1) break;
            if(c == 'A') 
            if(c == 'B')
            if(c == 'C')
            if(c == 'D')
                continue;
        }
        else {
            ++text.totalCharacters;
            ++text.currentRow->totalCnodes;
            text.currentPosition->c = c;
            text.currentPosition->next = calloc(1, sizeof(struct Cnode));
            text.currentPosition = text.currentPosition->next;
        }
    }
    finishEditor(&e);
    /*
    int fd = open("test", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    write(fd, buffer, i);
    */
    return 0;
}
