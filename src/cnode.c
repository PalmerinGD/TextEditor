#include "cnode.h"

struct cnode * createcnode(char c) {
    struct cnode * aux = malloc(sizeof(struct cnode));
    aux->next = NULL;
    aux->prev = NULL;
    aux->c = c;
    if(aux == NULL) exit(1);
    return aux;
}

void initcnodeList(struct cnodeList * clist) {
    clist->size = 0;
    clist->begin = clist->end = clist->currentcnode = createcnode(0);
}

/* Add a cnode to the cnodeTable in the current cnodelist */
int addcnode(struct cnodeList * clist, char c) {
    struct cnode * aux = createcnode(c);
    aux->next = clist->currentcnode->next;
    clist->currentcnode->next = aux;
    aux->prev = clist->currentcnode;
    clist->currentcnode = aux;
    if(c != 0) clist->size++;
}

int printcnodeList(int fd, struct cnodeList * clist) {
    size_t totalBytes = clist->size;
    char * buffer = malloc(totalBytes + 1);
    struct cnode * aux = clist->begin;
    int i = 0;
    while(aux != NULL) {
        if(aux->c != 0) buffer[i++] = aux->c;
        aux = aux->next;
    }
    buffer[i] = '\0';
    if(write(fd, buffer, i+1) != i+1) {
        exit(1);
    }
    return 0;
}

int getTotalcnodesAfter(struct cnode * cn) {
    int total = 0;
    int cnt = 0;
    while(cn != NULL && cnt <= 1) {
        if(cn->c == 0) cnt++;
        else if(cn->c != '\r' && cn->c != '\n') total++;
        cn = cn->next;
    }
    return total;
}

int getTotalcnodesBefore(struct cnode * cn) {
    int total = 0;
    while(cn != NULL && cn->c != 0) {
        if(cn->c != '\r' && cn->c != '\n') total++;
        cn = cn->prev;
    }
    return total;
}

struct cnode * cnodeParent(struct cnode * cn) {
    if(cn != NULL && cn->c == 0) cn = cn->prev;
    while(cn != NULL && cn->c != 0) cn = cn->prev;
    return cn;
}

int movecnode(struct cnodeList * clist, int n) {
    for(int i=0; i<n; i++) {
        clist->currentcnode = clist->currentcnode->next;
    }
    return 0;
}
