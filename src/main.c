#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "cnode.h"
#include "editor.h"
#include "systemopt.h"

#define ESC '\x1b'
#define ENTER 13
#define IS_RUNNING 1
#define CTRL_KEY(k) ((k & 0x1f))

int main() {
    struct systemopt sy;
    sy.row = 1;
    sy.col = 1;
    initEditor(&sy);

    struct cnodeList clist;
    initcnodeList(&clist);

    char key;
    while(IS_RUNNING) {
        refreshScreen();
        printcnodeList(STDOUT_FILENO, &clist);
        moveCursor(sy.row, sy.col);
        if(read(STDIN_FILENO, &key, 1) == -1) break;
        if(key == CTRL_KEY('q')) break;
        else if(key == ENTER) {
            addcnode(&clist, '\r');
            addcnode(&clist, '\n');
            addcnode(&clist, 0);
            ++sy.row;
            sy.col = 1;
        }
        else if(key == ESC) {
            char buffer[2];
            if(read(STDIN_FILENO, buffer, 2) == -1) break;
            if(buffer[0] != '[') continue;
            else if(buffer[1] == 'A') {
                if(clist.currentcnode->c == 0) {
                    struct cnode * parent = cnodeParent(clist.currentcnode);
                    clist.currentcnode = parent;
                    sy.col = 1;
                    --sy.row;
                }
                else {
                    struct cnode * parent = cnodeParent(clist.currentcnode);
                    struct cnode * grand = cnodeParent(parent);
                    if(grand != NULL) {
                        int totalc = getTotalcnodesBefore(clist.currentcnode);
                        int totalp = getTotalcnodesAfter(grand);
                        clist.currentcnode = grand;
                        --sy.row;
                        if(totalc > totalp) {
                            movecnode(&clist, totalp);
                            sy.col = totalp + 1;
                        }
                        else movecnode(&clist, totalc);
                    }
                }
            }
            else if(buffer[1] == 'B') break;
            else if(buffer[1] == 'C') break;
            else if(buffer[1] == 'D') break;
        }
        else {
            addcnode(&clist, key);
            ++sy.col;
        }
    }
    finishEditor(&sy);
    return 0;
}
