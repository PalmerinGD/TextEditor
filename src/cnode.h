#include <stdlib.h>
#include <stdio.h>

struct cnode {
    char c;
    struct cnode * next;
    struct cnode * prev;
};

struct  cnodeList{
    unsigned int len;
    struct cnode * begin;
    struct cnode * end;
};

struct cnodeTable {
    // Size of CnodeArr
    unsigned int lencnodeListArr;
    // Cnode array
    struct cnodeList * cnodeListArr;

    struct cnodeList * currentcnodeList;
    struct cnode * currentcnode;
};

int initcnodeTable(struct cnodeTable * ctable);
int addcnode(struct cnodeTable * ctable);
