/*
Author: Diego Palmerin
*/

#include "cnode.h"

/*
 * struct cnode * createcnode(char c)
 * description: Creates a new cnode with the value c and returns its reference.*/
struct cnode * createcnode(char c) {

    struct cnode * aux = malloc(sizeof(struct cnode));
    if(aux == NULL) exit(1);
    aux->next = NULL;
    aux->prev = NULL;
    aux->c = c;
    return aux;

}


/*
 * void initcnodeList(struct cnodeList * clist)
 * description: Initializes a cnodeList with only one line.*/
void initcnodeList(struct cnodeList * clist) {

    // BEGIN_LINE character is only used to indicate when a new line starts. 
    // They are not put in the final string.
    clist->size = 0;
    clist->totalLines = 1;
    clist->begin = clist->currentcnode = createcnode(BEGIN_LINE);

}


/* int addcnode(struct cnodeList * clist, char c)
 * description: Inserts a new cnode in the current position.*/
int addcnode(struct cnodeList * clist, char c) {

    struct cnode * newChar = createcnode(c);

    if(c != ENTER) {

        // The new cnode is inserted in between two cnodes.
        newChar->next = clist->currentcnode->next;
        if(newChar->next != NULL) 
            newChar->next->prev = newChar;

        clist->currentcnode->next = newChar;
        newChar->prev = clist->currentcnode;

        clist->currentcnode = newChar;
        clist->size++;

    } 

    else {

        // Create a new cnode that will hold the character of BEGIN_LINE.
        struct cnode * nextcnode = clist->currentcnode->next;
        struct cnode * newLine = createcnode(BEGIN_LINE); // New cnode corresponding to BEGIN_LINE
        clist->currentcnode->next = newChar;
        if(nextcnode == NULL || nextcnode->c != ENTER) 
            newChar->prev = clist->currentcnode;
        else newChar->prev = nextcnode->prev;
        newChar->next = newLine;
        newLine->prev = newChar;
        if(nextcnode != NULL) {
            newLine->next = nextcnode;
            nextcnode->prev = newLine;
        }
        // Increment by 2 the total size for '\r' and '\n'
        clist->currentcnode = newLine;
        clist->size += 2;
        clist->totalLines++;
    }
}


int movecnodeLeft(struct cnodeList * clist) {
    struct cnode * prevcnode = clist->currentcnode->prev;
    if(prevcnode == NULL || clist->currentcnode->c == BEGIN_LINE) return 0;
    clist->currentcnode = prevcnode;
    return 1;
}

int movecnodeRight(struct cnodeList * clist) {
    struct cnode * nextcnode = clist->currentcnode->next;
    if(nextcnode == NULL || nextcnode->c == ENTER) return 0;
    clist->currentcnode = nextcnode;
    return 1;
}

int movecnodeUp(struct cnodeList * clist) {
    int cnt = 0;
    int total = 0;
    struct cnode * aux = clist->currentcnode;
    while(aux != NULL && cnt < 2) {
        if(aux->c == BEGIN_LINE) {
            cnt++;
            if(cnt == 2) break;
        }
        else if(cnt == 0)total++;
        aux = aux->prev;
    }
    if(cnt != 2) return 0;
    int row = 1;
    while(total > 0 && aux->next != NULL && aux->next->c != ENTER) {
        total--;
        row++;
        aux = aux->next;
    }
    clist->currentcnode = aux;
    return row;
}

int movecnodeDown(struct cnodeList * clist) {
    int cnt = 0;
    struct cnode * aux = clist->currentcnode;
    struct cnode * aux2 = clist->currentcnode;
    while(aux2->c != BEGIN_LINE) {
        cnt++;
        aux2 = aux2->prev;
    }
    int total = 0;
    if(aux->c != BEGIN_LINE) total=1;
    while(aux != NULL && total < 2) {
        if(aux->c == BEGIN_LINE) {
            total++;
            if(total == 2) break;
        }
        aux = aux->next;
    }
    if(aux == NULL || total != 2) return 0;
    int row = 1;
    while(cnt > 0 && aux->next != NULL && aux->next->c != ENTER) {
        cnt--;
        row++;
        aux = aux->next;
    }
    clist->currentcnode = aux;
    return row;
}

int deletecnode(struct cnodeList * clist) {
    // If the current cnode is BEGIN_LINE
    struct cnode * aux = clist->currentcnode;
    if(aux->c == BEGIN_LINE) {
        struct cnode * paux = aux->prev;
        if(paux != NULL && paux->c == ENTER) {
            clist->currentcnode = paux->prev;
            clist->currentcnode->next = aux->next;
            if(aux->next != NULL)
                aux->next->prev = clist->currentcnode;
            free(paux);
            free(aux);
            clist->size -= 2;
            clist->totalLines--;
        }
        else return -1;
    }
    else {
        clist->currentcnode = aux->prev;
        if(aux->next != NULL) {
            aux->prev->next = aux->next;
            aux->next->prev = aux->prev;
        }
        else {
            aux->prev->next = NULL;
        }
        free(aux);
        clist->size--;
    }
    int col = 0;
    aux = clist->currentcnode;
    while(aux->c != BEGIN_LINE) {
        col++;
        aux = aux->prev;
    }
    return col + 1;
}

char * getcnodeListToString(struct cnodeList * clist) {
    size_t totalBytes = clist->size;
    char * buffer = malloc(totalBytes + 1);
    struct cnode * aux = clist->begin;
    int i = 0;
    while(aux != NULL) {
        if(aux->c == ENTER) {
            buffer[i++] = '\r';
            buffer[i++] = '\n';
        }
        else if(aux->c != BEGIN_LINE) buffer[i++] = aux->c;
        aux = aux->next;
    }
    buffer[i] = '\0';
    return buffer;
}
