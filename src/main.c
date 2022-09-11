#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "editor.h"


int main() {
    struct editor e;

    initEditor(&e);
    
    char key=0;



    while(IS_RUNNING) {
        // Refresh screen to see new changes
        refreshScreen();
        // Prints the text in the specified file descriptor
        printTextToScreen(STDOUT_FILENO, &e);
        // Update the cursor to the last position it had previously.
        //printf("\r\n%d %d\r\n", e.row, e.col);
        
        
        updateCursor(e.row, e.col);

        if(read(STDIN_FILENO, &key, 1) == -1) break;

        if(key == CTRL_KEY('q')) break;
        else if(key == ESC) {
            char buffer[2];
            if(read(STDIN_FILENO, buffer, 2) == -1) break;
            if(buffer[0] != '[') continue;
            else if(buffer[1] == 'A') moveCursorUp(&e);
            else if(buffer[1] == 'B') moveCursorDown(&e);
            else if(buffer[1] == 'C') moveCursorRight(&e);
            else if(buffer[1] == 'D') moveCursorLeft(&e);
        }
        else if(key == 127) deleteCharacter(&e);
        else addCharacter(&e, key);
    }

    finishEditor(&e);

    return 0;
}
