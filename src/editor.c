#include "editor.h"

int getTotalRows(struct editor * e) {
    return e->sy.ws.ws_row;
}
int getTotalCols(struct editor * e) {
    return e->sy.ws.ws_col;
}
void initEditor(struct editor * e) {

    initcnodeList(&e->cl);
    initSystemOpt(&e->sy);
    e->row = 1;
    e->col = 5;
    e->totalRows = e->sy.ws.ws_row;
    e->totalColumns = e->sy.ws.ws_col;
    e->offsetPosition = 5;

}

void updateOffsetPosition(struct editor * e) {
    if(e->cl.totalLines < 100) {
        /* _xx_*/
        e->offsetPosition = 5;
    }
    else if(e->cl.totalLines < 1000) {
        /* _xxx_*/
        e->offsetPosition = 6;
    }
    else {
        /*_xxxx_*/
        e->offsetPosition = 7;
    }
}

int printTextToScreen(int fd, struct editor * e) {
    // Buffer holds the final state of the text editor.
    char * buffer = getcnodeListToString(&e->cl);

    if(buffer == NULL) {
        printf("printText");
        exit(1);
    }

    int bufferLength = strlen(buffer);

    unsigned int totalLines = e->cl.totalLines;


    unsigned int finalBufferLength = bufferLength;
    int len;

    if(totalLines < 100) {
        /* _xx_*/
        finalBufferLength += 4 * totalLines;
        len = 4;
    }
    else if(totalLines < 1000) {
        /* _xxx_*/
        finalBufferLength += 5 * totalLines;
        len = 5;
    }
    else {
        /*_xxxx_*/
        finalBufferLength += 6 * totalLines;
        len = 6;
    }

    finalBufferLength++;

    char * finalBuffer = malloc(sizeof(char) * finalBufferLength);
    if(finalBuffer == NULL) {
        printf("FinalBuffer\n");
        exit(1);
    }
    memset(finalBuffer, ' ', finalBufferLength);


    char numberLine[len];
    memset(numberLine,' ',len);
    numberLine[len-2] = '0';
    int k = 0;

    for(int i=0; i<bufferLength; i++) {
        if(i == 0 || buffer[i-1] == '\n') {
            int j = len-2;
            int carry = 1;
            while(j > 0 && carry > 0) {
                if(numberLine[j] == ' ') numberLine[j] = '0';
                int sum = (numberLine[j] - '0') + carry;
                int aux = (sum % 10);
                numberLine[j] = '0' + aux;
                j--;
                if(sum >= 10) carry = 1;
                else carry = 0;
            }
            int aux = 0;
            while(aux < len) {
                finalBuffer[k++] = numberLine[aux++];
            }
            //finalBuffer[k++] = '1';
            //if(k >= finalBufferLength) break;
        }
        finalBuffer[k++] = buffer[i];
        //if(k >= finalBufferLength) break;
        //last = buffer[i];
    }
    if(bufferLength == 0 || buffer[bufferLength - 1] == '\n') {
        int j = len-2;
        int carry = 1;
        while(j > 0 && carry > 0) {
            if(numberLine[j] == ' ') numberLine[j] = '0';
            int sum = (numberLine[j] - '0') + carry;
            int aux = (sum % 10);
            numberLine[j] = '0' + aux;
            j--;
            if(sum >= 10) carry = 1;
            else carry = 0;
        }
        int aux = 0;
        while(aux < len) {
            finalBuffer[k++] = numberLine[aux++];
        }
    }

    finalBuffer[finalBufferLength-1] = '\0';

    if(write(fd, finalBuffer, finalBufferLength) != finalBufferLength) {
        printf("printText");
        exit(1);
    }
    free(buffer);
    free(finalBuffer);
}

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

void updateCursor(const unsigned int row, const unsigned int col) {
    char pos[100];
    memset(pos, '\0', 100);
    int temp = sprintf(pos, "\x1b[%d;%dH", row, col);
    ssize_t totalbytes = strlen(pos);
    if(write(STDOUT_FILENO, pos, totalbytes) != totalbytes) {
        printf("moveCursor");
        exit(1);
    }
}

void moveCursorUp(struct editor * e) {
    int col = movecnodeUp(&e->cl);
    if(col) {
        e->row--;
        e->col = col + e->offsetPosition - 1;
    }
}
void moveCursorDown(struct editor * e) {
    int col = movecnodeDown(&e->cl);
    if(col) {
        e->row++;
        e->col = col + e->offsetPosition - 1;
    }
}

void moveCursorRight(struct editor * e) {
    if(movecnodeRight(&e->cl)) ++(e->col);
}
void moveCursorLeft(struct editor * e) {
    if(movecnodeLeft(&e->cl)) --(e->col);
}

void addCharacter(struct editor * e, char c) {
    if(c == ENTER_KEY) {
        addcnode(&e->cl, ENTER);
        if(e->row < e->totalRows)
            ++(e->row);
        /*
        if(e->row < 100) {
            e->offsetPosition = 5;
        }
        else if(e->row < 1000) {
            e->offsetPosition = 6;
        }
        else {
            e->offsetPosition = 7;
        }
        */
        updateOffsetPosition(e);
        e->col = e->offsetPosition;
    }
    else {
        addcnode(&e->cl, c);
        ++(e->col);
    }
}

void deleteCharacter(struct editor * e) {

    char characterToDelete = e->cl.currentcnode->c;
    int col = deletecnode(&e->cl);
    if(col < 0) return;
    if(col >= e->col) {
        updateOffsetPosition(e);
    }
    if(characterToDelete == BEGIN_LINE && e->cl.totalLines < e->totalRows) --(e->row);
    e->col = e->offsetPosition + col - 1;
}

void finishEditor(struct editor * e) {
    finishSystemOpt(&e->sy);
}
