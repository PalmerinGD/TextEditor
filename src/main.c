#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "cnode.h"
#include "systemopt.h"

#define ENTER 13
#define IS_RUNNING 1
#define CTRL_KEY(k) ((k & 0x1f))

void refreshScreen();
void printText(struct cnodeTable * ctable);

int main() {
    struct systemopt sy;
    initEditor(&sy);

    struct cnodeTable table;
    initcnodeTable(&table);

    char c;
    while(IS_RUNNING) {
        refreshScreen();
        printText(&table);

        if(read(STDIN_FILENO, &c, 1) == -1) break;
        if(c == CTRL_KEY('q')) break;
        else if(c == ENTER) {
            continue;
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
            table.currentcnode->c = c;
            ++(table.currentcnodeList->len);
            addcnode(&table);
        }
    }
    finishEditor(&sy);
    return 0;
}

void refreshScreen() {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
}

void printText(struct cnodeTable * ctable) {
    for(int i=0; i<ctable->lencnodeListArr; i++) {
        int totalBytesToWrite = ctable->cnodeListArr[i].len;
        if(totalBytesToWrite == 0) continue;
        char * buffer = calloc(totalBytesToWrite, 1);
        struct cnode * cn = ctable->cnodeListArr[i].begin;
        for(int j=0; j<(int)totalBytesToWrite; j++) {
            buffer[j] = cn->c;
            cn = cn->next;
        }
        write(STDOUT_FILENO, buffer, totalBytesToWrite);
        free(buffer);
    }
}
