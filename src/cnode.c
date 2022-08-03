#include "cnode.h"

int initcnodeTable(struct cnodeTable * ctable) {
    ctable->lencnodeListArr = 1;
    ctable->cnodeListArr = NULL;

    ctable->currentcnode = NULL;
    ctable->currentcnodeList = NULL;

    ctable->cnodeListArr = calloc(1,sizeof(struct cnodeList));
    if(ctable->cnodeListArr == NULL) {
        return -1;
    }
    ctable->currentcnodeList = ctable->cnodeListArr;



    ctable->currentcnodeList->len = 0;
    ctable->currentcnodeList->begin = NULL;
    ctable->currentcnodeList->end = NULL;

    return addcnode(ctable);
    

}

/* Add a cnode to the cnodeTable in the current position */
int addcnode(struct cnodeTable * ctable) {
    struct cnode * newcnode = calloc(1, sizeof(struct cnode));
    if(newcnode == NULL) {
        return -1;
    }
    else {
        newcnode->prev = NULL;
        newcnode->next = NULL;
        newcnode->c = 0;

        if(ctable->currentcnodeList->len > 0) {

            ctable->currentcnode->next = newcnode;
            newcnode->prev = ctable->currentcnode;
            ctable->currentcnode = newcnode;
            ctable->currentcnodeList->end = newcnode;

        }
        else {
            ctable->currentcnodeList->begin = newcnode;
            ctable->currentcnodeList->end = newcnode;
            ctable->currentcnode = newcnode;
        }

        return 0;
    }
}


